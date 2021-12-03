#include "pipex.h"
static int	ft_words(char *s, char c);

static int	ft_copy(char *arr, char *s, char c, int pos);

static char	**ft_fill(char **arr, int words, char const *s, char c);

static void	ft_free(char **arr, int i);

char	**ft_split_commands(char *s, char c)
{
	char	**arr;
	int		words;

	if (!s)
		return (0);
	words = ft_words((char *)s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (0);
	ft_fill(arr, words, s, c);
	if (!arr)
		return (0);
	return (arr);
}

static char	**ft_fill(char **arr, int words, char const *s, char c)
{
	int		i;
	int		len;
	int		pos;

	i = 0;
	pos = 0;
	while (words > 0)
	{
		while (s[pos] == c)
			pos++;
		len = 0;
		while (s[pos + len] != 0 && s[pos + len] != c)
			len++;
		arr[i] = malloc(len * sizeof(char) + 1);
		if (!arr[i])
		{
			ft_free(arr, i);
			return (0);
		}
		pos = ft_copy(arr[i], (char *)s, c, pos);
		words--;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

static void	ft_free(char **arr, int i)
{
	while (i > 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

static int	ft_words(char *s, char c)
{
	int	trigger;
	int	w;

	trigger = 0;
	w = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			if (*s == '\'' || *s == '\"')
			{
				s++;
				while (*s != '\'' && *s != '\"')
					s++;
			}
			trigger = 1;
			w++;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (w);
}

static int	ft_copy(char *arr, char *s, char c, int pos)
{
	int	i;

	i = 0;
	if (s[pos] == '\'' || s[pos] == '\"')
	{
		pos++;
		while (s[pos + 1] != '\0')
		{
			arr[i] = s[pos];
			pos++;
			i++;
		}
	}
	else
	{
		while (s[pos] != '\0' && s[pos] != c)
		{
			arr[i] = s[pos];
			pos++;
			i++;
		}
	}
	arr[i] = '\0';
	return (pos);
}
