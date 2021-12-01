#include "pipex.h"
#include <stdlib.h>
char	**ft_get_commands(char **argv, int len)
{
	char	**commands;
	int		i;
	int		j;

	i = 2;
	j = 0;
	commands = malloc((len + 1) * sizeof(char *));
	commands[len] = NULL;
	while (j < len)
	{
		commands[j] = argv[i];
		i++;
		j++;
	}
	return (commands);
}
