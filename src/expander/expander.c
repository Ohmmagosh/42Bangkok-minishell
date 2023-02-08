/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 01:27:24 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 13:03:06 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
