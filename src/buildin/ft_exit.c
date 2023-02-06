/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:26:28 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/06 20:52:05 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_lex(t_pro *p)
{
	t_llst	*tmp;
	t_llst	*tmp_del;

	tmp = p->lex.lst;
	while (tmp != NULL)
	{
		tmp_del = tmp;
		tmp = tmp->next;
		if (!tmp_del->content)
		{
			free(tmp_del->content);
			tmp_del->content = NULL;
		}
		if (!tmp_del)
		{
			free(tmp_del);
			tmp_del = NULL;
		}
	}
}

void	free_par(t_pro *p)
{
	int	i = 0;
	int	j = 0;

	while (i < p->par.size)
	{
		j = 0;
		if (!p->par.cmd[i].cmd)
		{
			free(p->par.cmd[i].cmd);
			p->par.cmd[i].cmd = NULL;
		}
		if (!p->par.cmd[i].error)
		{
			free(p->par.cmd[i].error);
			p->par.cmd[i].error = NULL;
		}
		while (p->par.cmd[i].allcmd[j])
		{
			if (!p->par.cmd[i].allcmd[j])
			{
				free(p->par.cmd[i].allcmd[j]);
				p->par.cmd[i].allcmd[j] = NULL;
			}
			j++;
		}
		i++;
	}
	if (!p->par.cmd)
		free(p->par.cmd);
	p->par.cmd = NULL;
}

void	ft_exit(t_pro *p)
{
	ft_lstclr(&(p->ownenv));
	free_par(p);
	free_lex(p);
}
