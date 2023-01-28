/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 01:27:24 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/28 17:30:19 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// #include <limits.h>
// #include <stddef.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>

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
char	*ft_expand(char *ptr, t_pro *p)
{
	char	*t_ptrc;

	t_ptrc = ft_clenvar(ptr);
	// printf("\n aft clean:%s\n", t_ptrc);
	free(ptr);
	printf("%s----------hello----------%s\n", "\e[42m", "\e[0m");
	return (t_ptrc);
}

// st is a start charactor
// end is an end charactor
char	*ft_strcreate(char *st, char *end)
{
	size_t	siz_str;
	char	*res;
	char	*t_res;

	res = NULL;
	// printf("str create\npst:%p pend:%p\n", st, end);
	if (end >= st)
	{
		siz_str = end - st;
		res = malloc(sizeof(char) * (siz_str + 2));
		if (res != NULL)
		{
			t_res = res;
			while (st != end)
			{
				*t_res = *st;
				st++;
				t_res++;
			}
			*t_res = *st;
			t_res++;
			*t_res = '\0';
		}
	}
	return (res);
}

// envname must be sent since $
char	*ft_getenv(char **ptrst, char **ptrend)
{
	char	*pchr;
	char	*envst;
	char	*envend;

	printf("getenv\n");
	envst = *ptrst;
	envend = envst + 1;
	printf("bef while envst:%s envend:%s\n", envst, envend);
	fflush(stdout);
	while ((*envend != ' ') && (*envend != '\'') && \
			(*envend != '\"') && (*envend != '$') && (*envend != '\0'))
		envend++;
	printf("end while envst:%s envend:%s\n", envst, envend);
	printf("envst:%d envend:%d\n", (int)(*envst), (int)(*envend));
	fflush(stdout);
	pchr = ft_strcreate(envst, (envend - 1));
	// printf("bef chg $ 2  @\n");
	// fflush(stdout);
	// *pchr = '@';
	*ptrend = envend;
	return (pchr);
}

void	ft_joinres(char **t_res, char **t_str)
{
	char	*res;
	char	*t_res0;
	char	*t_res1;

	res = *t_res;
	t_res0 = *t_str;
	if (res == NULL)
		res = t_res0;
	else
	{
		t_res1 = ft_strjoin(res, t_res0);
		free(res);
		free(t_res0);
		res = t_res1;
	}
	*t_res = res;
}

char	*ft_getres(char *t_ptrst, char *t_ptrend, char **t_res)
{
	char	*ptrst;
	char	*ptrend;
	char	*t_res0;

	ptrst = t_ptrst;
	ptrend = t_ptrend;
	// printf("getres st:%s end:%s\n", ptrst, ptrend);
	// fflush(stdout);
	// t_res0 = ft_strcreate(ptrst + 1, ptrend - 1);
	t_res0 = ft_strcreate(ptrst, ptrend);
	ft_joinres(t_res, &t_res0);

	// if (res == NULL)
	// 	res = t_res0;
	// else
	// {
	// 	t_res1 = ft_strjoin(res, t_res0);
	// 	free(res);
	// 	free(t_res0);
	// 	res = t_res1;
	// }

	// if (*ptrend != '\0')
	// 	ptrst = ptrend + 1;
	// else
	// 	ptrst = ptrend;

	ptrst = ptrend;
	
	// *t_res = res;
	return (ptrst);
}

char	*ft_clenptr(char *ptr)
{
	char	*ptrst;
	char	*ptrend;
	char	*res;
	char	*t_res0;
	// char	*t_res1;

	int	i = 0;

	ptrst = ptr;
	res = NULL;
	while (*ptrst != '\0')
	// while ((*ptrst != '\0') && (i < 10))
	{
		if (*ptrst == '\'')
		{
			ptrend = ptrst + 1;
			while ((*ptrend != '\'') && (*ptrend != '\0'))
				ptrend++;
			ptrst = ft_getres(ptrst + 1, ptrend - 1, &res) + 2;
			// t_res0 = ft_strcreate(ptrst + 1, ptrend - 1);
			// if (res == NULL)
			// {
			// 	res = t_res0;
			// }
			// else
			// {
			// 	t_res1 = ft_strjoin(res, t_res0);
			// 	free(res);
			// 	free(t_res0);
			// 	res = t_res1;
			// }
			// // if (*ptrend != '\0')
			// // 	ptrst = ptrend + 1;
			// // else
			// // 	ptrst = ptrend;
			// ptrst = (ptrend + 1);
		}
		else if (*ptrst == '\"')
		{
			// printf("case \"\n");
			ptrst = ptrst + 1;
			ptrend = ptrst;
			// printf("bef \" ptr st:%s end:%s\n", ptrst, ptrend);
			while (*ptrst != '\"')
			// while ((*ptrst != '\"') && (i < 10))
			{
				while ((*ptrend != '\"') && (*ptrend != '$') && (*ptrend != '\0'))
					ptrend++;
				if (*ptrst != '$')
				{
					ptrst = ft_getres(ptrst, ptrend - 1, &res) + 1;
					// zt_res0 = ft_strcreate(ptrst, ptrend - 1);
					// if (res == NULL)
					// {
					// 	res = t_res0;
					// }
					// else
					// {
					// 	t_res1 = ft_strjoin(res, t_res0);
					// 	free(res);
					// 	free(t_res0);
					// 	res = t_res1;
					// }
					// // printf("case \" bef trans ptr st:%s end:%s res:%s\n", ptrst, ptrend, res);
					// ptrst = (ptrend);
					// i++;
				}
				// "@$he 'll'o",
				// found env
				else
				{
					t_res0 = ft_getenv(&ptrst, &ptrend);
					ft_joinres(&res, &t_res0);

					// if (res == NULL)
					// {
					// 	res = t_res0;
					// }
					// else
					// {
					// 	t_res1 = ft_strjoin(res, t_res0);
					// 	free(res);
					// 	free(t_res0);
					// 	res = t_res1;
					// }

					// if (*ptrend != '\0')
					// 	ptrst = ptrend + 1;
					// else
					// 	ptrst = ptrend;

					// if (*ptrend != '\"')
					// 	ptrst = ptrend;
					// else
					//  	ptrst = (ptrend + 1);

					ptrst = ptrend;
				}
				// printf("case \" ptr st:%s end:%s res:%s\n", ptrst, ptrend, res);
				// fflush(stdout);
			}
			ptrst = ptrst + 1;
		}
		else if (*ptrst == '$')
		{
			// printf("case env\n");
			// fflush(stdout);

			t_res0 = ft_getenv(&ptrst, &ptrend);
			ft_joinres(&res, &t_res0);

			// if (res == NULL)
			// {
			// 	res = t_res0;
			// }
			// else
			// {
			// 	t_res1 = ft_strjoin(res, t_res0);
			// 	free(res);
			// 	free(t_res0);
			// 	res = t_res1;
			// }

			// printf("bef trans ptr st:%s end:%s\n", ptrst, ptrend);
			// if (*ptrend != '\0')
			// 	ptrst = ptrend + 1;
			// else
			// 	ptrst = ptrend;
			
			ptrst = ptrend;
		}
		else
		{
			// printf("case char\n");
			// fflush(stdout);
			ptrend = ptrst + 1;
			while ((*ptrend != '\'') && (*ptrend != '\"') && \
				(*ptrend != '$') && (*ptrend != '\0'))
				ptrend++;
			// t_res0 = ft_strcreate((ptrst + 1), (ptrend - 1));
			ptrst = ft_getres(ptrst, ptrend - 1, &res);

			// t_res0 = ft_strcreate((ptrst), (ptrend - 1));
			// if (res == NULL)
			// {
			// 	res = t_res0;
			// }
			// else
			// {
			// 	t_res1 = ft_strjoin(res, t_res0);
			// 	free(res);
			// 	free(t_res0);
			// 	res = t_res1;
			// }

			// if (*ptrend != '\0')
			// 	ptrst = ptrend + 1;
			// else
			// 	ptrst = ptrend;

			ptrst = ptrend;

			// printf("st:%s end:%s\n", ptrst, ptrend);
			// printf("res:%s\n", res);
			// fflush(stdout);
		}
		// if (*ptrst != '\0')
		// // if ((*ptrst != '$') && (*ptrst != '\0'))
		// 	ptrst++;
		i++;
	}
	return (res);
}

// 0 no need absolute path
// 1 need absolute path
// char	*ft_expander(char *ptr, t_pro *p, int cmdabpath)
char	*ft_expand(char *ptr, t_pro *p)
// char	*ft_expander(char *ptr)
{
	char	*res;
	(void)p;

	res = ft_clenptr(ptr);
	free(ptr);
	return (res);
}

// int	main (void)
// {
// 	char	ex[10][30] = {"\'$HOME\'",
// 							"\"hello\"",
// 							"\"e\"\"c\"\"h\"\"o\"",
// 							"\"he'll'o\"",
// 							"he'll'o",
// 							"@$HOME@",
// 							"\"$HOME\"",
// 							"@$he 'll'o",
// 							"\0"};
// 	// char	ex[10][20];
// 	char	*t_ex;
// 	char	*t_res;

// 	printf("before:%s\n", ex[0]);
// 	t_ex = ft_strdup(ex[0]);
// 	t_res = ft_expander(t_ex);
// 	printf("aft:%s\n\n", t_res);
// 	free(t_res);

// 	printf("before:%s\n", ex[1]);
// 	t_ex = ft_strdup(ex[1]);
// 	t_res = ft_expander(t_ex);
// 	printf("aft:%s\n\n", t_res);
// 	free(t_res);

// 	printf("before:%s\n", ex[2]);
// 	t_ex = ft_strdup(ex[2]);
// 	t_res = ft_expander(t_ex);
// 	printf("aft:%s\n\n", t_res);
// 	free(t_res);

// 	printf("before:%s\n", ex[3]);
// 	t_ex = ft_strdup(ex[3]);
// 	t_res = ft_expander(t_ex);
// 	printf("aft:%s\n\n", t_res);
// 	free(t_res);

// 	printf("before:%s\n", ex[4]);
// 	t_ex = ft_strdup(ex[4]);
// 	t_res = ft_expander(t_ex);
// 	printf("aft:%s\n\n", t_res);
// 	free(t_res);

// 	printf("before:%s\n", ex[5]);
// 	t_ex = ft_strdup(ex[5]);
// 	t_res = ft_expander(t_ex);
// 	printf("aft:%s\n\n", t_res);
// 	free(t_res);

// 	printf("before:%s\n", ex[6]);
// 	t_ex = ft_strdup(ex[6]);
// 	t_res = ft_expander(t_ex);
// 	printf("aft:%s\n\n", t_res);
// 	free(t_res);

// 	printf("before:%s\n", ex[7]);
// 	t_ex = ft_strdup(ex[7]);
// 	t_res = ft_expander(t_ex);
// 	printf("aft:%s\n\n", t_res);
// 	free(t_res);

// 	return (0);
// }

// int    main(void)
// {
// //   char  ret[8][20] = {"\"hello\"", "\"he'll'o\"", "\"e\"\"c\"\"h\"\"o\"", "he'll'o", "\"$HOME\"","'$HOME'", NULL };
// 	char	**t_ptr;
// 	char	**tmp_ptr;
// 	char	*res;
// 	char	str1[30] = "'$HOME'";
// 	char	str2[30] = "\"e\"\"c\"\"h\"\"o\"";
// 	char	str3[30] = "\"he'll'o\"";
// 	// char	str3[30] = ""e""c""h""o"";
// 	char	str4[30] = "\"hello\"";
// 	char	str5[30] = "he'll'o";
// 	char	str6[30] = "\"$HOME\"";

// 	"echo", "ls", "-la", NULL

// 	t_ptr = malloc(sizeof(char *) * 7);
// 	if (t_ptr != NULL)
// 	{
// 		tmp_ptr = t_ptr;
// 		tmp_ptr[0] = ft_strdup(str1);
// 		tmp_ptr[1] = ft_strdup(str2);
// 		tmp_ptr[2] = ft_strdup(str3);
// 		tmp_ptr[3] = ft_strdup(str4);
// 		tmp_ptr[4] = ft_strdup(str5);
// 		tmp_ptr[5] = ft_strdup(str6);
// 		tmp_ptr[6] = NULL;

// 		while (*tmp_ptr != NULL)
// 		{
// 			// ft_printd(*tmp_ptr);
// 			ft_putstr("Example\n");
// 			ft_putstr(*tmp_ptr);
// 			ft_putstr("\n");
// 			res = ft_expand(*tmp_ptr);
// 			ft_putstr("aft\n");
// 			ft_putstr(res);
// 			ft_putstr("\n");
// 			ft_putstr("\n");
// 			tmp_ptr++;
// 		}
// 		// free(t_ptr);

// 		// while (*tmp_ptr != NULL)
// 		// {
// 		// 	*tmp_ptr = ft_expand(*tmp_ptr);
// 		// 	tmp_ptr++;
// 		// }
// 	}
// }
void	print_chk_cmd(t_pro	*p)
{
	int	i = 0;
	int	j = 0;
	while (i < p->par.size)
	{
		printf("index %d\n",p->par.cmd[i].index);
		printf("cmd 1 %s\n", p->par.cmd[i].cmd);
		j = 0;
		printf("-----------cmd %d------------\n", i);
		printf("p->par.cmd[i].re.infd -> %d\n", p->par.cmd[i].re.infd);
		printf("p->par.cmd[i].re.outfd -> %d\n", p->par.cmd[i].re.outfd);
		while (p->par.cmd[i].allcmd[j])
		{
			printf("%d %s\n", j,p->par.cmd[i].allcmd[j]);
			j++;
		}
		i++;
	}
}

void	new_expand(t_cmd *cmd, t_pro *p)
{
	int	i;

	i = 0;
	while (cmd->allcmd[i])
	{
		cmd->allcmd[i] = ft_expand(cmd->allcmd[i], p);
		i++;
	}
}

void	expander(t_pro *p)
{
	int	i;

	i = 0;
	while (i < p->par.size)
	{
		new_expand(&p->par.cmd[i], p);
		if (p->par.cmd[i].allcmd == NULL)
			p->par.cmd[i].cmd = NULL;
		else
			p->par.cmd[i].cmd = ft_strdup(p->par.cmd[i].allcmd[0]);
		i++;
	}
	printf("%s----------hello expand----------%s\n", "\e[42m", "\e[0m");
	print_chk_cmd(p);
}