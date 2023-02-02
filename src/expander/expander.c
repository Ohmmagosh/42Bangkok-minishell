/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 01:27:24 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/02 00:01:08 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_freesplit(char ***split)
{
	char	**t_split;

	t_split = *split;
	while (*t_split != NULL)
	{
		free(*t_split);
		t_split++;
	}
	t_split = *split;
	free(t_split);
	*split = NULL;
}

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
char	*ft_getenvval(char **ptrst, char **ptrend, t_pro *p)
{
	char	*pchr;
	char	*penv;
	char	*envst;
	char	*envend;

	(void)p;
	printf("getenvval\n");
	envst = *ptrst;
	envend = envst + 1;
	printf("bef while envst:%s envend:%s\n", envst, envend);
	fflush(stdout);
	while ((*envend != ' ') && (*envend != '\'') && \
			(*envend != '\"') && (*envend != '$') && (*envend != '\0'))
		envend++;
	pchr = ft_strcreate(envst, (envend - 1));
	printf("end while envst:%s envend:%s\n", envst, envend);
	printf("envst:%d envend:%d\n", (int)(*envst), (int)(*envend));
	printf("env name:%s\n", pchr);
	penv = ft_getenv(&p->ownenv, pchr);
	if (penv != NULL)
	{
		printf("env val:%s\n", penv);
		ft_cutenvval(&penv);
		printf("env val aft cut:%s\n", penv);
		fflush(stdout);
	}
	else
	{
		printf("env Not found\n");
		penv = ft_calloc(1, 1);
		printf("env str:%s\n", penv);
		fflush(stdout);
	}
	fflush(stdout);
	// printf("bef chg $ 2  @\n");
	// fflush(stdout);
	// *pchr = '@';
	free(pchr);
	*ptrend = envend;
	// return (pchr);
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

char	*ft_clenptr(char *ptr, t_pro *p)
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
				// printf("case \" ptr st:%s end:%s res:%s\n", ptrst, ptrend, res);
				// fflush(stdout);
			}
			ptrst = ptrst + 1;
		}
		else if (*ptrst == '$')
		{
			// printf("case env\n");
			// fflush(stdout);

			t_res0 = ft_getenvval(&ptrst, &ptrend, p);
			printf("case $ res0:%s\n", t_res0);
			fflush(stdout);
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

// // ""ls"
// //  "-la""
// // return 1
// // ""ls"
// //  "cat"
// // return 0
// int	ft_cmdlen(char **str)
// {

// }

char	*ft_cratetestpath(char *path, char *cmd)
{
	char	*t_path;
	char	*t_cmd;

	t_path = join_char(path, '/');
	// printf("add / to path:%s\n", t_path);
	// printf("cmd:%s\n", cmd);
	// fflush(stdout);
	t_cmd = cmd;
	while (*t_cmd != '\0')
	{
		t_path = join_char(t_path, *t_cmd);
		t_cmd++;
	}
	t_path = join_char(t_path, *t_cmd);
	printf("full create path:%s\n", t_path);
	fflush(stdout);
	// free(t_path);
	return (t_path);
}

// ******* need to free split and check leak ************
void	ft_getabpath(char **cmd, t_pro *p)
{
	char	*t_cmd;
	char	*t_path;
	char	**t_spitpath;
	char	**spitpath;
	char	*t_chr;

	// printf("get aboslute path of cmd\n");
	t_cmd = *cmd;
	if ( (ft_strncmp(t_cmd, "echo", ft_strlen(t_cmd)) != 0) && (ft_strncmp(t_cmd, "cd", ft_strlen(t_cmd)) != 0) && \
		(ft_strncmp(t_cmd, "pwd", ft_strlen(t_cmd)) != 0) && (ft_strncmp(t_cmd, "export", ft_strlen(t_cmd)) != 0) && \
		(ft_strncmp(t_cmd, "unset", ft_strlen(t_cmd)) != 0) && (ft_strncmp(t_cmd, "env", ft_strlen(t_cmd)) != 0) && \
		(ft_strncmp(t_cmd, "exit", ft_strlen(t_cmd)) != 0) )
	{
		// printf("Found cmd not built-in\n");
		// fflush(stdout);

		t_path = ft_getenv(&p->ownenv, "$PATH");
		ft_cutenvval(&t_path);
		spitpath = ft_split(t_path, ':');
		t_spitpath = spitpath;
		if (t_path != NULL)
			free(t_path);
		while (*t_spitpath != NULL)
		{
			// printf("path:%s\n", *t_spitpath);
			t_chr = ft_cratetestpath(*t_spitpath, t_cmd);
			if ((ft_chk_perm(t_chr) & (0b0001)) != 0)
			{
				printf("found correct path\n");
				break ;
			}
			else
			{
				printf("not correct path\n");
				free(t_chr);
			}
			t_spitpath++;
		}
		// ft_freesplit(&spitpath);
		*cmd = t_chr;
		free(t_cmd);
	}
}

// 0 no need absolute path
// 1 need absolute path
// char	*ft_expander(char *ptr, t_pro *p, int cmdabpath)
char	*ft_expand(char *ptr, t_pro *p, int cmdabpath)
// char	*ft_expand(char *ptr, t_pro *p)
// char	*ft_expander(char *ptr)
{
	char	*res;
	char	*envpath;

	res = ft_clenptr(ptr, p);
	// printf("cmd:%s\n", res);
	// fflush(stdout);
	if (cmdabpath == 1)
	{
		ft_getabpath(&res, p);
		printf("show absolute path:%s\n", res);
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
	//printf("%s----------hello expand----------%s\n", "\e[42m", "\e[0m");
	while (i < p->par.size)
	{
		new_expand(&p->par.cmd[i], p);
		if (p->par.cmd[i].allcmd == NULL)
			p->par.cmd[i].cmd = NULL;
		else
			p->par.cmd[i].cmd = ft_strdup(p->par.cmd[i].allcmd[0]);
		i++;
	}
	//print_chk_cmd(p);
}
