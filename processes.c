#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
void	ft_child_process(int fd, t_pipe pipex, int *pipefd)
{
	int	i;

	i = 0;
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(fd);
	while (pipex.paths[i])
	{
		pipex.cmd1 = ft_strjoin(pipex.paths[i], pipex.cmd1_flag[0]);
		execve(pipex.cmd1, &pipex.cmd1_flag[1], pipex.envp);
		free(pipex.cmd1);
		i++;
	}
	exit(EXIT_FAILURE);
}

void	ft_parent_process(int fd, t_pipe pipex, int *pipefd)
{
	int	status;
	int	i;

	i = 0;
	waitpid(-1, &status, 0);
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[0], STDOUT_FILENO);
	close(pipefd[1]);
	close(fd);
	while (pipex.paths[i])
	{
		pipex.cmd2 = ft_strjoin(pipex.paths[i], pipex.cmd2_flag[0]);
		perror(pipex.paths[i]);
		execve(pipex.cmd2, &pipex.cmd2_flag[1], pipex.envp);
		perror("Error");
		free(pipex.cmd2);
		i++;
	}
	exit(EXIT_FAILURE);
}
