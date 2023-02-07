/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 01:27:24 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 04:49:46 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

// return
// bit 0 = execute
// bit 1 = write
// bit 2 = read
// bit 3 = file exist
char	ft_chk_perm(char *path)
{
	char	permission;

	permission = 0;
	if (access(path, F_OK) == 0)
		permission = (permission | (0b1000));
	if (access(path, R_OK) == 0)
		permission = (permission | (0b0100));
	if (access(path, W_OK) == 0)
		permission = (permission | (0b0010));
	if (access(path, X_OK) == 0)
		permission = (permission | (0b0001));
	return (permission);
}

// st is a start charactor
// end is an end charactor
char	*ft_strcreate(char *st, char *end)
{
	size_t	siz_str;
	char	*res;
	char	*t_res;

	res = NULL;
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
char	*ft_getenvval(char **ptrst, char **ptrend, t_pro *p)
{
	char	*pchr;
	char	*penv;
	char	*envst;
	char	*envend;

	envst = *ptrst;
	envend = envst + 1;
	while ((*envend != ' ') && (*envend != '\'') && \
			(*envend != '\"') && (*envend != '$') && (*envend != '\0'))
		envend++;
	pchr = ft_strcreate(envst, (envend - 1));
	penv = ft_getenv(&p->ownenv, pchr);
	if (penv != NULL)
		ft_cutenvval(&penv);
	else
		penv = ft_calloc(1, 1);
	free(pchr);
	*ptrend = envend;
	return (penv);
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
	t_res0 = ft_strcreate(ptrst, ptrend);
	ft_joinres(t_res, &t_res0);
	ptrst = ptrend;
	return (ptrst);
}

char	*ft_clenptr(char *ptr, t_pro *p)
{
	char	*ptrst;
	char	*ptrend;
	char	*res;
	char	*t_res0;

	ptrst = ptr;
	res = NULL;
	while (*ptrst != '\0')
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
			ptrst = ptrst + 1;
			ptrend = ptrst;
			while (*ptrst != '\"')
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
				else
				{
					t_res0 = ft_getenvval(&ptrst, &ptrend, p);
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
			}
			ptrst = ptrst + 1;
		}
		else if (*ptrst == '$')
		{
			t_res0 = ft_getenvval(&ptrst, &ptrend, p);
			// dprintf(2, "expander $? t_res0 aft:%s\n", t_res0);
			// fflush(stderr);
			// printf("case $ res0:%s\n", t_res0);
			// fflush(stdout);
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
			ptrend = ptrst + 1;
			while ((*ptrend != '\'') && (*ptrend != '\"') && \
				(*ptrend != '$') && (*ptrend != '\0'))
				ptrend++;
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
		}
		// if (*ptrst != '\0')
		// // if ((*ptrst != '$') && (*ptrst != '\0'))
		// 	ptrst++;
		// i++;
	}
	return (res);
}

// 0 no need absolute path
// 1 need absolute path
// return NULL if cmd "ls" cannot get absolut path
char	*ft_expand(char *ptr, t_pro *p, int cmdabpath)
{
	char	*res;
	char	*envpath;

	res = ft_clenptr(ptr, p);
	if (cmdabpath == 1)
	{
		ft_getabpath(&res, p);
	}
	free(ptr);
	return (res);
}

//void	print_chk_cmd(t_pro	*p)
//{
//	int	i = 0;
//	int	j = 0;
//	while (i < p->par.size)
//	{
//		printf("index %d\n",p->par.cmd[i].index);
//		printf("cmd 1 %s\n", p->par.cmd[i].cmd);
//		j = 0;
//		printf("-----------cmd %d------------\n", i);
//		printf("p->par.cmd[i].re.infd -> %d\n", p->par.cmd[i].re.infd);
//		printf("p->par.cmd[i].re.outfd -> %d\n", p->par.cmd[i].re.outfd);
//		while (p->par.cmd[i].allcmd[j])
//		{
//			printf("%d %s\n", j,p->par.cmd[i].allcmd[j]);
//			j++;
//		}
//		i++;
//	}
//}

void	new_expand(t_cmd *cmd, t_pro *p)
{
	int	i;

	i = 0;
	while (cmd->allcmd[i])
	{
		if (i == 0)
			cmd->allcmd[i] = ft_expand(cmd->allcmd[i], p, 1);
		else
			cmd->allcmd[i] = ft_expand(cmd->allcmd[i], p, 0);
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
		if (p->par.cmd[i].allcmd != NULL)
		{
			p->par.cmd[i].cmd = NULL;
		}
		else
		{
			p->par.cmd[i].cmd = ft_strdup(p->par.cmd[i].allcmd[0]);
		}
		i++;
	}
}
