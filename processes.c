#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
void	ft_child1_process(t_pipe pipex, int *pipefd, char **envp)
{
	int	i;

	i = 0;
	dup2(pipex.infile, STDIN_FILENO);
	close(pipex.infile);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	while (pipex.paths[i])
	{
		pipex.cmd1 = ft_strjoin(pipex.paths[i], pipex.cmd1_flag[0]);
		if (!access(pipex.cmd1, F_OK & X_OK))
			execve(pipex.cmd1, pipex.cmd1_flag, envp);
		free(pipex.cmd1);
		i++;
	}
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(pipex.cmd1_flag[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	ft_child2_process(t_pipe pipex, int *pipefd, char **envp)
{
	int	i;

	i = 0;
	dup2(pipefd[0], STDIN_FILENO);
	dup2(pipex.outfile, STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	while (pipex.paths[i])
	{
		pipex.cmd2 = ft_strjoin(pipex.paths[i], pipex.cmd2_flag[0]);
		if (!access(pipex.cmd2, F_OK & X_OK))
			execve(pipex.cmd2, pipex.cmd2_flag, envp);
		free(pipex.cmd2);
		i++;
	}
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(pipex.cmd2_flag[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}
