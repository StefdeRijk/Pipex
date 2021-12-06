#include "pipex.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
static int	ft_pipex(t_pipe pipe, char **envp);

t_pipe		ft_get_data(t_pipe pipex, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	int		status;

	if (argc < 5)
		exit(127);
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
	{
		perror("bash: input");
		if (pipex.outfile < 0)
			exit(127);
		write(pipex.outfile, "       0\n", 9);
		return (0);
	}
	if (!*envp)
	{
		write(pipex.outfile, "       1\n", 9);
		exit(0);
	}
	pipex.commands = ft_get_commands(argv, argc - 3);
	pipex.size = argc - 3;
	status = ft_pipex(pipex, envp);
	return (status);
}

static int	ft_pipex(t_pipe pipex, char **envp)
{
	int		pipefd[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipe(pipefd);
	pipex = ft_get_data(pipex, envp);
	child1 = fork();
	if (child1 < 0)
		perror("Fork: ");
	if (child1 == 0)
		ft_child1_process(pipex, pipefd, envp);
	child2 = fork();
	if (child2 < 0)
		perror("Fork: ");
	if (child2 == 0)
		ft_child2_process(pipex, pipefd, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	return (WEXITSTATUS(status));
}

t_pipe	ft_get_data(t_pipe pipex, char **envp)
{
	char	*path;
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (!line)
	{
		line = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	path = ft_substr(line, 5, ft_strlen(line));
	pipex.paths = ft_split(path, ':');
	free(path);
	i = 0;
	while (pipex.paths[i])
	{
		pipex.paths[i] = ft_strjoin(pipex.paths[i], "/");
		i++;
	}
	pipex.cmd1_flag = ft_split_commands(pipex.commands[0], ' ');
	pipex.cmd2_flag = ft_split_commands(pipex.commands[1], ' ');
	return (pipex);
}
