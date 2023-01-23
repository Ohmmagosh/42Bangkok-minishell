
#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	ismetastr(char *s)
{
	if (s == NULL)
		return (0);
	if (!ft_strncmp(s, "<", 2))
		return (1);
	else if (!ft_strncmp(s, "<<", 3))
		return (1);
	else if (!ft_strncmp(s, ">", 2))
		return (1);
	else if (!ft_strncmp(s, ">>", 3))
		return (1);
	return (0);
}

char	*newrealloc(char *s)
{
	free(s);
	s = ft_calloc(1, 1);
	return (s);
}

void	free_split(char **bye)
{
	int	i;

	i = 0;
	if (!bye)
		return;
	while (bye[i])
	{
		free(bye[i]);
		i++;
	}
	free(bye);
}
int	new_str_len(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if(ft_strncmp(str[i], "", 1))
			len++;
		i++;
	}
	return (len);
}

char	**new_str_utils(char **str)
{
	char	**ret;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = new_str_len(str);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if(ft_strncmp(str[i], "", 1))
		{
			ret[j] = ft_strdup(str[i]);
			j++;
		}
		i++;
	}
	ret[j] = NULL;
	return (ret);
}

char	**new_str(char **cmd)
{
	int	i;
	char	**ret;

	i = 0;
	ret = NULL;
	while (cmd[i])
	{
		if (ismetastr(cmd[i]) && cmd[i])
		{	
			cmd[i] = newrealloc(cmd[i]);
			if (cmd[i + 1])
				cmd[i + 1] = newrealloc(cmd[i + 1]);
		}
		i++;
	}
	i = 0;
	ret = new_str_utils(cmd);
	
	return (ret);
}

int	main(void)
{
	char	**s = ft_split("echo hello < hello < world > o1 > o2 << eof > o4", ' ');

	char	**ret;

	for (int i = 0; s[i]; i++)
		printf("s[i] -> %s\n", s[i]);
	ret = new_str(s);

	for (int i = 0; ret[i]; i++)
		printf("cmd[i] -> %s\n", ret[i]);

}