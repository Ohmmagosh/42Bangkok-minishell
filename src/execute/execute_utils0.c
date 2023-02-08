/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:02:06 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 16:04:35 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

void	ft_openpipe(t_cmd *p, int lencmd)
{
	int	i;

	i = 1;
	while (i < lencmd)
	{
		pipe(p[i].re.pfd);
		i++;
	}
}

void	ft_duprdwr(int *tmp_rd, int *tmp_wr)
{
	*tmp_rd = dup(0);
	*tmp_wr = dup(1);
}

void	ft_close0(t_cmd *p, int lencmd, int i)
{
	int	a;

	a = 1;
	while (a < lencmd)
	{
		close(p[a].re.pfd[0]);
		if (a != i + 1)
			close(p[a].re.pfd[1]);
		a++;
	}
	dup2(p[i + 1].re.pfd[1], STDOUT_FILENO);
}

void	ft_close1(t_cmd *p, int lencmd, int i)
{
	int	a;

	a = 1;
	while (a < lencmd)
	{
		close(p[a].re.pfd[1]);
		if (a != i)
			close(p[a].re.pfd[0]);
		a++;
	}
	dup2(p[i].re.pfd[0], STDIN_FILENO);
}

void	ft_closeunlink(t_cmd *p, int i)
{
	dup2(p[i].re.infd, STDIN_FILENO);
	dup2(p[i].re.outfd, STDOUT_FILENO);
	if (p[i].re.infd != 0)
		close(p[i].re.infd);
	if (p[i].re.outfd != 1)
		close(p[i].re.outfd);
	if (p[i].heredoc != NULL)
		unlink(p[i].heredoc);
}
