/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:13:59 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 13:02:40 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
