
#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	new_str(char *s1, char *s2)
{
	// char	*tmp;
	// char	*tmp2;

	s1 = ft_strdup("-----");
	s2 = ft_strdup("-----");
	// s1 = tmp;
	// s2 = tmp2;
}

int	main(void)
{
	// char **s =ft_split("hello world hiiiii", ' ');
	// for (int i = 0; s[i]; i++)
	// 	printf("s[i] -> %s\n", s[i]);
	// // new_str(s[1], s[3]);
	// printf("%s----------berfore new str----------%s\n", "\e[42m", "\e[0m");
	// for (int i = 0; s[i]; i++)
	// {
	// 	if (!ft_strncmp(s[i], "world", 6))
	// 	{
	// 		free(s[i]);
	// 		s[i] = ft_strdup("-----");
	// 		if (s[i + 1])
	// 		{
	// 			free(s[i + 1]);
	// 			s[i + 1] = ft_strdup("-----");
	// 		}	
	// 	}
	// }
	// for (int i = 0; s[i]; i++)
	// 	printf("s[i] -> %s\n", s[i]);
	// for (int i = 0; s[i]; i++)
	// 	free(s[i]);
	// free(s);
	char	*s[] = {"hello", NULL, "world", NULL};
	
	for (int i = 0; i < 3; i++)
		printf("%s\n", s[i]);
	
	for (int i = 0; i < 3; i++)
	{
		if (s[i] != NULL)
			free(s[i]);
	}
	free(s);
	
}