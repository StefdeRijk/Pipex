#include "pipex.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
static void	ft_pipex(t_pipe pipe);

t_pipe		ft_get_data(t_pipe pipex);

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	int		i;

	i = 0;
	if (argc < 5)
		return (0);
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	pipex.commands = ft_get_commands(argv, argc - 3);
	pipex.size = argc - 3;
	pipex.envp = envp;
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	ft_pipex(pipex);
	return (0);
}

static void	ft_pipex(t_pipe pipex)
{
	int		pipefd[2];
	pid_t	parent;

	pipe(pipefd);
	pipex = ft_get_data(pipex);
	parent = fork();
	if (!parent)
		ft_child_process(pipex.infile, pipex, pipefd);
	else
		ft_parent_process(pipex.outfile, pipex, pipefd);
}

t_pipe	ft_get_data(t_pipe pipex)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_substr(pipex.envp[7], 5, ft_strlen(pipex.envp[7]));
	pipex.paths = ft_split(path, ':');
	while (pipex.paths[i])
	{
		pipex.paths[i] = ft_strjoin(pipex.paths[i], "/");
		i++;
	}
	pipex.cmd1_flag = ft_split(pipex.commands[0], ' ');
	pipex.cmd2_flag = ft_split(pipex.commands[1], ' ');
	return (pipex);
}
