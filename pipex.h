#ifndef PIPEX_H
# define PIPEX_H

# include "./Libft/libft.h"

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		size;

	char	**envp;
	char	**commands;
	char	**paths;

	char	*cmd1;
	char	**cmd1_flag;
	char	*cmd2;
	char	**cmd2_flag;
}	t_pipe;

char	**ft_get_commands(char **argv, int len);

void	ft_child_process(int fd, t_pipe pipex, int *pipefd);
void	ft_parent_process(int fd, t_pipe pipex, int *pipefd);

#endif