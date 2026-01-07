#include <stdlib.h>		// exit
#include <unistd.h>		// pipe, fork, dup2, execvp, close
#include <stdio.h>		// printf
#include <sys/types.h> 	// pid_t

// Allowed functions: pipe, fork, dup2, execvp, close, exit

int ft_popen(const char *file, char *const argv[], char type);

int	main() {
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	dup2(fd, 0);
	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
	char	*line;
	while ((line = get_next_line(fd)))
		printf("%s", line);
}

int ft_popen(const char *file, char *const argv[], char type)
{
	int		pipefd[2];
	pid_t	pid;

	// Check args - accept only w and r type.
	if (!file || !argv || (type != 'w' && type != 'r'))
		return (-1);

	// Create pipe
	if (pipe(pipefd) == -1)
		return (-1);
	
	// Fork - Go into child process to modify stdin / stdout and execute.
	pid = fork();
	// 	On failure close pipes & exit.
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	//	On success:
	// In child:
	if (pid == 0)
	{
		if (type == 'r')	// If read - send commands STDOUT into pipe.
		{
			close(pipefd[0]);	// Close read end of pipe (unused in child - parent will read)
			dup2(pipefd[1], 1);	// Redirect stdout to pipe (child writes into pipe)
			close(pipefd[1]);	// Close write end of pipe.
		}
		else if (type == 'w') // If write - read commands STDIN from pipe.
		{
			close(pipefd[1]);	// Close write end of pipe. (unused in child - parent will write)
			dup2(pipefd[0], 0);	// Redirect stdin to read end (child reads from pipe)
			close(pipefd[0]);	// Close read end of pipe.
		}
		execvp(file, argv);	// Execute file with args.
		exit(1);			// Exit.
	}
	// In parent:
	if (type == 'r')		// If read:
	{
		close(pipefd[1]);	// Close write end.
		return (pipefd[0]); // Keep read end.
	}
	else					// If write:
	{
		close(pipefd[0]);	// Close read end.
		return (pipefd[1]);	// Keep write end.
	}
	}