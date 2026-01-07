// Create a "sandbox" that executes a function and determines
// wheter it is a "good" or "bad" function.
// Bad function:
//	- segfault
//	- abort
//	- timeout.
//	- exit_code != 0

// KEY CONCEPTS
// 4. ALARM: Set a tmeout for the function
// 1. SIGNALS: Handle SIGALARM for timeout
// 2. FORK: Execute the function in a separate process
// 3. WAITPID: Obtain information about how the process ended
// 5. SIGNAL HANDLING: Configure signal handlers

// LOGIC
// 1. Fork a child process to execute the function
// 2. In the parent: set alarm and wait with waitpid
// 3. Analyze hwo the process edned (normal, signal, timout)
// 4. Return 1 (good), 0 (bad) or -1 (error) (IF VERBOSE TRUE, WRITE AN ERROR MESSAGE)
// "Nice function!\n"
// "Bad function: exited with code <exit_code>\n"
// "Bad function: <signal description>\n"
// "Bad function: timed out after <timeout> seconds\n"

// Allowed functions: 
// fork, waitpid, exit, alarm, sigaction, kill, printf, strsignal,
// errno, sigaddset, sigemptyset, sigfillset, sigdelset, sigismember

#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void	alarm_handler(int sig)
{
	(void)sig;
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t				pid;
	int					status;
	struct sigaction	sa;
	
	// Set up signal handler
	sa.sa_handler = alarm_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGALRM, &sa, NULL);

	// Fork into child process to run function
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		f(); // Run function.
		exit(0); // Function terminated normally.
	}

	// Set up alarm (Sends a SIGALRM after timeout seconds)
	// This will interrupt waitpid().
	alarm(timeout);

	// Wait for child
	if (waitpid(pid, &status, 0) == -1)
	{
		// 1. Interrupted by SIGALARM
		if (errno == EINTR)
		{
			kill(pid, SIGKILL); 	// Kill the timedout (zombie) child process.
			waitpid(pid, NULL, 0); 	// Clean the zombie process (prev waitpid was interrupted, but process still running)
			if (verbose)			// If verbose == true, give error msg.
				printf("Bad function: timed out after %d seconds\n", timeout);
			return (0); 			// Return "bad function"
		}
		return (-1);				// Real waitpid() error
	}
	
	// Cancel pending alarm if child returns fast
	alarm(0);

	// 2. Returned normally
	if (WIFEXITED(status))
	{
		// Exited with SUCCESS
		if (WEXITSTATUS(status) == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);	// Return "good function";
		}
		// Exited with exit code != 0
		else
		{
			if (verbose)
				printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
			return (0); // Return "bad function"
		}
	}
	
	// 3. Terminated by signal (segfault, abort, etc.)
	if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (verbose)
			printf("Bad function: %s\n", strsignal(sig));
		return (0);	// "bad function"
	}
	// Error occured
	return (-1);
}