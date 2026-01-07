#include <stdio.h>		//printf
#include <stdlib.h>		//exit
#include <unistd.h>		//close, fork , wait, execvp, dup2, pipe
#include <sys/types.h>	//pid_t

// cmds = Null terminated array of commands (with arguments)
// Example...
// cmds[0] = {"ls", "-la", NULL}
// cmds[1] = {"grep", "txt", NULL}
// cmds[2] = NULL

// Return 1 error - 0 success.

// Logic:
// 1. For each command (except last one), create a pipe.
// 2. Fork a process for the current command.
// 3. In the child: Configure stdin/stdout and execute command.
// 4. In the parent: manage fds and continue with next command.
// 5. Wait for all processes to finish.

// Main loop:
//	- Process each command in the pipeline.
// Create pipe:
// 	- Only create pipe if there is a next command.
//	- This pie connect s the current command to the next one.
// FORK
// Child process:
//	- Configure stdin: if 'prev_fd' exists, then the command must be read from the previous pipe.
//	- Configure stdout: if there is a next command, the command must write to the current pipe.
//	- Execute command: cmds[i][0] is the command name - cmds[i] is the full arg list.
// Parent process:
//	- Close 'prev_fd' if it exists.
//	- For the current pipe:
//		- Close write end (pipe[1])
//		- Save read and as 'prev_fd' for the next command.
int picoshell(char **cmds[])
{
	pid_t	pid;
	int		pipefd[2];
	int		prev_fd;
	int		status;
	int		exit_code;
	int		i;

	if (!cmds)
		return (1);

	exit_code = 0;
	prev_fd = -1;
	i = 0;
	while (cmds[i])
	{
		// Not the last command - Create a pipe.
		// If pipe() fails, return error.
		if (cmds[i + 1] != NULL)
		{
			if (pipe(pipefd) == -1)
			{
				if (prev_fd != -1)
					close(prev_fd);
				return (1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			// Fork error.
			// If not last command (meaning a pipe was created for this command), close both ends.
			if (cmds[i + 1] != NULL)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			if (prev_fd != -1)
				close(prev_fd);
			return (1);
		}
		// IN CHILD.
		if (pid == 0)
		{
			// Configure STDIN.
			//	- If prev_fd has been set, this command must read from previous pipe.
			if (prev_fd != -1)
			{
				// Redirect stdin to 'prev_fd'
				if (dup2(prev_fd, STDIN_FILENO) == -1)
					exit(1);
				close (prev_fd);
			}
			// Configure STDOUT.
			//	- If there is a next command, redirect stdout to the new pipe.
			if (cmds[i + 1] != NULL)
			{
				close(pipefd[0]);	// Close unused read end.
				if (dup2(pipefd[1], STDOUT_FILENO) == -1)
					exit (1);
				close(pipefd[1]);
			}
			// Execute command.
			execvp(cmds[i][0], cmds[i]);
			exit(1); // If execvp fails.
		}
		// IN PARENT.
		// If prev_fd has been set - close the old prev_fd.
		if (prev_fd != -1)
			close(prev_fd);
		// If there is a next command:
		//	- close unsused write end.
		// 	- save read end as prev_fd for next command.
		if (cmds[i + 1] != NULL)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		// Move to next command.
		i++;
	}
	// WAIT FOR ALL CHILDREN
	while (wait(&status) != -1);
	return (exit_code);
}
