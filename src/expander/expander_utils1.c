/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:13:56 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 13:02:53 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_singlequote(char **t_ptrend, char **t_ptrst, char **t_res)
{
	char	*ptrend;
	char	*ptrst;
	char	*res;

	ptrend = *t_ptrend;
	ptrst = *t_ptrst;
	res = *t_res;
	ptrend = ptrst + 1;
	while ((*ptrend != '\'') && (*ptrend != '\0'))
		ptrend++;
	ptrst = ft_getres(ptrst + 1, ptrend - 1, &res) + 2;
	*t_ptrend = ptrend;
	*t_ptrst = ptrst;
	*t_res = res;
}

void	ft_dollarsign(char **t_ptrend, char **t_ptrst, char **t_res, t_pro *p)
{
	char	*t_res0;
	char	*ptrst;
	char	*ptrend;
	char	*res;

	ptrend = *t_ptrend;
	ptrst = *t_ptrst;
	res = *t_res;
	t_res0 = ft_getenvval(&ptrst, &ptrend, p);
	ft_joinres(&res, &t_res0);
	ptrst = ptrend;
	*t_ptrend = ptrend;
	*t_ptrst = ptrst;
	*t_res = res;
}

void	ft_doublequote(char **t_ptrend, char **t_ptrst, char **t_res, t_pro *p)
{
	char	*ptrst;
	char	*ptrend;
	char	*t_res0;
	char	*res;

	ptrst = *t_ptrst + 1;
	res = *t_res;
	ptrend = ptrst;
	while (*ptrst != '\"')
	{
		while ((*ptrend != '\"') && (*ptrend != '$') && (*ptrend != '\0'))
			ptrend++;
		if (*ptrst != '$')
			ptrst = ft_getres(ptrst, ptrend - 1, &res) + 1;
		else
			ft_dollarsign(&ptrend, &ptrst, &res, p);
	}
	*t_ptrst = ptrst + 1;
	*t_ptrend = ptrend;
	*t_res = res;
}

char	*ft_clenptr(char *ptr, t_pro *p)
{
	char	*ptrst;
	char	*ptrend;
	char	*res;

	ptrst = ptr;
	res = NULL;
	while (*ptrst != '\0')
	{
		if (*ptrst == '\'')
			ft_singlequote(&ptrend, &ptrst, &res);
		else if (*ptrst == '\"')
			ft_doublequote(&ptrend, &ptrst, &res, p);
		else if (*ptrst == '$')
			ft_dollarsign(&ptrend, &ptrst, &res, p);
		else
		{
			ptrend = ptrst + 1;
			while ((*ptrend != '\'') && (*ptrend != '\"') && \
				(*ptrend != '$') && (*ptrend != '\0'))
				ptrend++;
			ptrst = ft_getres(ptrst, ptrend - 1, &res);
			ptrst = ptrend;
		}
	}
	return (res);
}
