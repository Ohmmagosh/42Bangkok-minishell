/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:46:22 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 16:05:48 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

void	ft_childrun(t_cmd *p, int lencmd, int i, t_list **ownenv)
{
	if (i != lencmd - 1)
		ft_close0(p, lencmd, i);
	if (i != 0)
		ft_close1(p, lencmd, i);
	ft_closeunlink(p, i);
	ft_budn_child(p, i, ownenv);
}

void	ft_parentrun(t_cmd *p, int i, t_list **ownenv)
{
	ft_budn_parent(p, i, ownenv);
	if (i != 0)
	{
		close(p[i].re.pfd[0]);
		close(p[i].re.pfd[1]);
	}
}

void	ft_exitstatus(t_cmd *p, int lencmd, int *t_status)
{
	int		i;
	int		status;
	char	*cmd;

	status = *t_status;
	i = 0;
	while (i < lencmd)
	{
		waitpid(p[i].re.pid, &status, 0);
		if (p[i].allcmd[0] != NULL)
		{
			cmd = p[i].allcmd[0];
			if (!(((ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0) || \
				(ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0) || \
				(ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0) || \
				(ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0))))
			{
				status = WEXITSTATUS(status);
				g_status = status;
			}
		}
		i++;
	}
}

void	executer(t_cmd *p, char **env, int lencmd, t_list **ownenv)
{
	int	i;
	int	status;
	int	tmp_rd;
	int	tmp_wr;

	ft_openpipe(p, lencmd);
	i = 0;
	ft_duprdwr(&tmp_rd, &tmp_wr);
	while (i < lencmd)
	{
		p[i].re.pid = fork();
		if (p[i].re.pid == 0)
		{
			ft_childrun(p, lencmd, i, ownenv);
			status = execve(p[i].allcmd[0], p[i].allcmd, env);
		}
		else
		{
			ft_parentrun(p, i, ownenv);
			dup2(tmp_rd, 0);
			dup2(tmp_wr, 1);
		}
		i++;
	}
	ft_exitstatus(p, lencmd, &status);
}

void	execute(t_pro *p, char **env)
{
	g_status = 0;
	executer(p->par.cmd, env, p->par.size, &(p->ownenv));
	free_par(p);
	free_lex(p);
}
