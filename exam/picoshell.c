#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define RD 0
#define WR 1

int picoshell(char *arg[][3])
{
	int pipefd[2];
	int temp_fd = 0;

	for (int i = 0; i < 3; i ++)
	{
		if (pipe(pipefd) < 0)
			return -1;
		pid_t pid = fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				close(STDOUT_FILENO);
				dup(pipefd[WR]);
				// dup2(pipefd[WR], STDOUT_FILENO);
				close(pipefd[RD]);
				close(pipefd[WR]);
			}
			if (i == 1)
			{
				dup2(temp_fd, STDIN_FILENO);
				dup2(pipefd[WR], STDOUT_FILENO);
				close(pipefd[RD]);
				close(pipefd[WR]);
			}
			if (i == 2)
			{
				dup2(temp_fd, STDIN_FILENO);
				close(pipefd[RD]);
				close(pipefd[WR]);
			}
			execvp(arg[i][0], arg[i]);
		}
		// temp_fd = dup(pipefd[RD]);
		dup2(pipefd[RD], temp_fd);
		close(pipefd[RD]);
		close(pipefd[WR]);
	}
	waitpid(-1, NULL, 0);
	return 1;
}

int main(void)
{
	char *argv[][3] = {
		[0] = {"echo", "hello\nworld", NULL},
		[1] = {"grep", "w", NULL},
		[2] = {"wc", "-c", NULL},
		[3] = NULL
	};

	int ret = picoshell(argv);
	return 0;
}
