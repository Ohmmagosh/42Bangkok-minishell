/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 01:27:24 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/22 01:09:44 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// string is what between double quote
// arg is what between single quote
// if it is multiple string
// multiple strings must be combine together
// if it is multiple arg
// multiple args must be combine together

// int	chk_quote(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{

// 	}
// 	return (i);
// }

// char	*expander(char *s)
// {
// 	int		i;
// 	char	*ret;
// 	char	*tmp;

// 	ret = NULL;
// 	i = 0;
// 	tmp = ft_calloc(1, 1);
// 	while (s[i])
// 	{
// 		if (s[i] == '\"')
// 		{

// 		}
// 		else if (s[i] == '\'')
// 		{
// 		}
// 		else if (ft_isalnum(s[i]))
// 		{
// 		}
// 		i++;
// 	}
// 	return (ret);
// }

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		len;
	char	*s2;
	int		i;

	i = 0;
	len = (int)ft_strlen(s1);
	s2 = (char *)malloc((len + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = s1[i];
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str1;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = (ft_strlen(s1) + ft_strlen(s2));
	str1 = (char *)malloc(sizeof(char) * i + 1);
	if (!str1)
		return (NULL);
	while (*s1)
		*str1++ = *s1++;
	while (*s2)
		*str1++ = *s2++;
	*str1 = '\0';
	str1 = str1 - i;
	return ((char *)str1);
}

// for debug
void	ft_putstr(char *str)
{
	if (str != NULL)
	{
		while (*str != '\0')
		{
			write(1, str, 1);
			str++;
		}
	}
}

// for debug
void	ft_printd(char *ptr)
{
	while (*ptr != '\0')
	{
		printf("%d ", (int)(*ptr));
		ptr++;
	}
	printf("\n");
}

// st is the 1st charactor
// end is the last charactor
char	*ft_strcrate(char *st, char *end)
{
	size_t	size;
	char	*res;
	char	*t_res;

	printf("\nstr create st:%s,end:%s\n", st, end);
	size = end - st;
	res = malloc((sizeof(char) * size) + 1);
	t_res = res;
	if (t_res != NULL)
	{
		while (st != end)
		{
			*t_res = *st;
			t_res++;
			st++;
		}
		*t_res = *st;
		t_res++;
		*t_res = '\0';
	}
	// printf("\nstr create:%s\n", res);
	return (res);
}

// env string
// literal string
char	*ft_clenvar(char *ptr)
{
	char	*t_ptrst;
	char	*t_ptrend;
	char	*res;
	char	*t_chr0;
	char	*t_chr1;

	t_ptrst = ptr;
	res = NULL;
	// printf("in clean\n");
	while (*t_ptrst != '\0')
	{
		if (*t_ptrst == '\'')
		{
			// printf("found case:\' \n");
			t_ptrend = t_ptrst + 1;
			while (*t_ptrend != *t_ptrst)
				t_ptrend++;
			// printf("bef:%c test:%c\n",*(t_ptrst + 1) ,*(t_ptrend - 1));

			if (res == NULL)
				res = ft_strcrate((t_ptrst + 1), (t_ptrend - 1));
			else
			{
				t_chr0 = ft_strcrate((t_ptrst + 1), (t_ptrend - 1));
				t_chr1 = ft_strjoin(res, t_chr0);
				free(res);
				free(t_chr0);
				res = t_chr1;
				free(t_chr1);
			}
			// printf("\nres aft if:%s\n", res);
		}
		else if (*t_ptrst == '\"')
		{
			// printf("found case:\"\n");
			t_ptrend = t_ptrst + 1;
			// printf("bef while\n");
			// printf("prtend:%s\n", t_ptrend);
			// while ((*t_ptrend != *t_ptrst) && (*t_ptrend != '$') && (*t_ptrend != '\0'))
			while ((*t_ptrend != *t_ptrst) && (*t_ptrend != '$'))
				t_ptrend++;
			// printf("after while\n");
			// printf("end:%s\n", t_ptrend);
			// normal case
			if (*t_ptrend == *t_ptrst)
			{
				// printf("\nnormal case\"\n");
				if (res == NULL)
				{
					// printf("res eq null\n");
					res = ft_strcrate((t_ptrst + 1), (t_ptrend - 1));
					// printf("res:%s\n", res);
				}
				else
				{
					// printf("\nres not null\n");
					t_chr0 = ft_strcrate((t_ptrst + 1), (t_ptrend - 1));
					// printf("\nbef str join\nres:%s str create:%s\n", res, t_chr0);
					t_chr1 = ft_strjoin(res, t_chr0);
					// printf("\naft str join:%s\n", t_chr1);
					free(res);
					free(t_chr0);
					res = t_chr1;
					// printf("res:%s\n", res);
				}
			}
			// case finding env
			else
			{
				printf("\n\ncase find env\n\n");
				if ((t_ptrend - t_ptrst) == 1)
					printf("found env immediat\n");
				else
				{
					printf("found char before env\n");
					if (res == NULL)
					{
						// printf("res eq null\n");
						res = ft_strcrate((t_ptrst + 1), (t_ptrend - 1));
						// printf("res:%s\n", res);
					}
					else
					{
						// printf("\nres not null\n");
						t_chr0 = ft_strcrate((t_ptrst + 1), (t_ptrend - 1));
						// printf("\nbef str join\nres:%s str create:%s\n", res, t_chr0);
						t_chr1 = ft_strjoin(res, t_chr0);
						// printf("\naft str join:%s\n", t_chr1);
						free(res);
						free(t_chr0);
						res = t_chr1;
						// printf("res:%s\n", res);
					}
					printf("res:%s\n", res);
				}
				// t_ptrst = t_ptrend + 1;
				t_ptrst = t_ptrend;
				printf("bef st:%s\n", t_ptrst);
				t_ptrend = t_ptrst + 1;
				printf("st:%s end:%s\n", t_ptrst, t_ptrend);
				while ((*t_ptrend != ' ') && (*t_ptrend != '\"'))
					t_ptrend++;
				printf("st:%s end:%s\n", t_ptrst, t_ptrend);
				// t_chr0 = ft_strcrate((t_ptrst + 1), (t_ptrend - 1));
				t_chr0 = ft_strcrate((t_ptrst), (t_ptrend - 1));
				if (t_chr0 != NULL)
					printf("searhing for env:%s\n", t_chr0);
				else
					printf("str create err\n");
				printf("res:%s, env:%s\n", res, t_chr0);

				if (res != NULL)
				{	
					t_chr1 = ft_strjoin(res, t_chr0);
					free(t_chr0);
					free(res);
					res = t_chr1;
				}
				else

				res = t_chr1;
				t_ptrst = t_ptrend;
				t_ptrend = t_ptrst + 1;

				while (*t_ptrend != '\"')
					t_ptrend++;
				t_chr0 = ft_strcrate((t_ptrst + 1), (t_ptrend - 1));
				t_chr1 = ft_strjoin(res, t_chr0);
				free(t_chr0);
				free(t_chr1);
				res = t_chr1;
			}
		}
		else
		{
			t_ptrend = t_ptrst + 1;
			while ((*t_ptrend != '\'') && (*t_ptrend != '\"') && (*t_ptrend != '$'))
				t_ptrend++;
			if (res == NULL)
			{
				// printf("res eq null\n");
				res = ft_strcrate((t_ptrst + 1), (t_ptrend - 1));
				// printf("res:%s\n", res);
			}
			else
			{
				// printf("\nres not null\n");
				t_chr0 = ft_strcrate((t_ptrst + 1), (t_ptrend - 1));
				// printf("\nbef str join\nres:%s str create:%s\n", res, t_chr0);
				t_chr1 = ft_strjoin(res, t_chr0);
				// printf("\naft str join:%s\n", t_chr1);
				free(res);
				free(t_chr0);
				res = t_chr1;
				// printf("res:%s\n", res);
			}
		}
		t_ptrst = t_ptrend + 1;
		// printf("\nend pair\n");
		// printf("res:%s\n\n", res);
	}
	// free(ptr);
	return (res);
}

// cmdabpath == 1 need absolute path of cmd
// cmdabpath == 0 no need absolute path of cmd
char	*ft_expand(char *ptr, t_pro *p, int *cmdabpath)
{
	char	*t_ptrc;

	t_ptrc = ft_clenvar(ptr);
	// printf("\n aft clean:%s\n", t_ptrc);
	free(ptr);
	return (t_ptrc);
}

int    main(void)
{
//   char  ret[8][20] = {"\"hello\"", "\"he'll'o\"", "\"e\"\"c\"\"h\"\"o\"", "he'll'o", "\"$HOME\"","'$HOME'", NULL };
	char	**t_ptr;
	char	**tmp_ptr;
	char	*res;
	char	str1[30] = "'$HOME'";
	char	str2[30] = "\"e\"\"c\"\"h\"\"o\"";
	char	str3[30] = "\"he'll'o\"";
	// char	str3[30] = ""e""c""h""o"";
	char	str4[30] = "\"hello\"";
	char	str5[30] = "he'll'o";
	char	str6[30] = "\"$HOME\"";

	"echo", "ls", "-la", NULL

	t_ptr = malloc(sizeof(char *) * 7);
	if (t_ptr != NULL)
	{
		tmp_ptr = t_ptr;
		tmp_ptr[0] = ft_strdup(str1);
		tmp_ptr[1] = ft_strdup(str2);
		tmp_ptr[2] = ft_strdup(str3);
		tmp_ptr[3] = ft_strdup(str4);
		tmp_ptr[4] = ft_strdup(str5);
		tmp_ptr[5] = ft_strdup(str6);
		tmp_ptr[6] = NULL;

		while (*tmp_ptr != NULL)
		{
			// ft_printd(*tmp_ptr);
			ft_putstr("Example\n");
			ft_putstr(*tmp_ptr);
			ft_putstr("\n");
			res = ft_expand(*tmp_ptr);
			ft_putstr("aft\n");
			ft_putstr(res);
			ft_putstr("\n");
			ft_putstr("\n");
			tmp_ptr++;
		}
		// free(t_ptr);

		// while (*tmp_ptr != NULL)
		// {
		// 	*tmp_ptr = ft_expand(*tmp_ptr);
		// 	tmp_ptr++;
		// }
	}
}
