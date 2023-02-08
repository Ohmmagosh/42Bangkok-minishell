/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:02:09 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 16:04:33 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

int	ft_chkbuldnconparent(char *cmd)
{
	if ((ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0) || \
		(ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0) || \
		(ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0) || \
		(ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0) || \
		(ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0) || \
		(ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0))
		return (1);
	else
		return (0);
}

void	ft_budn_parent(t_cmd *p, int i, t_list **ownenv)
{
	char	*cmd;

	if (p[i].allcmd[0] == (void *)0)
		return ;
	if (ft_chkbuldnconparent(p[i].allcmd[0]))
	{
		cmd = p[i].allcmd[0];
		if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		{
			if (p[i].allcmd[1] != NULL)
				ft_export(ownenv, p[i].allcmd[1]);
			else
				ft_exportnull(ownenv);
		}
		else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
			ft_unset(ownenv, p[i].allcmd[1]);
		else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
			ft_cd(ownenv, p[i].allcmd[1]);
	}
}

int	ft_chkbuldnconchild(char *cmd)
{
	if ((ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0) || \
		(ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0) || \
		(ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0) || \
		(ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0) || \
		(ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0) || \
		(ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0) || \
		(ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0))
		return (1);
	else
		return (0);
}

void	ft_budn_child(t_cmd *p, int i, t_list **ownenv)
{
	char	*cmd0;
	char	*cmd1;

	if (p[i].allcmd[0] == (void *)0)
		exit(1);
	if (ft_chkbuldnconchild(p[i].allcmd[0]))
	{
		cmd0 = p[i].allcmd[0];
		if (ft_strncmp(cmd0, "pwd", ft_strlen(cmd0)) == 0)
			ft_pwd(ownenv);
		else if (ft_strncmp(cmd0, "echo", ft_strlen(cmd0)) == 0)
		{
			cmd1 = p[i].allcmd[1];
			if (ft_strncmp(cmd1, "-n", ft_strlen(cmd1)) == 0)
				ft_echowtopt(p[i].allcmd);
			else
				ft_echonoopt(p[i].allcmd);
		}
		else if (ft_strncmp(cmd0, "env", ft_strlen(cmd0)) == 0)
			ft_env(ownenv);
		exit (0);
	}
}
