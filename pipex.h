#ifndef PIPEX_H
# define PIPEX_H

# include "./Libft/libft.h"

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		size;
	int		iter;

	char	**commands;
	char	**paths;

	char	*cmd;
	char	**cmd_flag;
}	t_pipe;

char	**ft_get_commands(char **argv, int len);
char	**ft_split_commands(char const *s, char c);
void	ft_close_pipes(t_pipe pipex, int *pipefd);

void	ft_child_process(t_pipe pipex, int *pipefd, char **envp);

#endif