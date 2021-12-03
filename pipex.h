#ifndef PIPEX_H
# define PIPEX_H

# include "./Libft/libft.h"

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		size;

	char	**commands;
	char	**paths;

	char	*cmd1;
	char	**cmd1_flag;
	char	*cmd2;
	char	**cmd2_flag;
}	t_pipe;

char	**ft_get_commands(char **argv, int len);
char	**ft_split_commands(char *s, char c);

void	ft_child1_process(t_pipe pipex, int *pipefd, char **envp);
void	ft_child2_process(t_pipe pipex, int *pipefd, char **envp);

#endif