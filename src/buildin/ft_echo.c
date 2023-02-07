/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:46:05 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/07 16:49:42 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

void	ft_echonoopt(char **allcmd)
{
	char	**t_allcmd;
	// int		i;

	// i = 0;
	// dprintf(2, "echo fn\n");
	// fflush(stdout);
	t_allcmd = allcmd + 1;
	// dprintf(2, "allcmd:%s, arg:%s\n", *allcmd, *t_allcmd);
	while (*t_allcmd != NULL)
	{
		// printf("%s\n", *t_allcmd);
		// fflush(stdout);
		ft_putstr_fd(*t_allcmd, 1);
		if ((t_allcmd + 1) != NULL)
			ft_putstr_fd(" ", 1);
		// dprintf(2, "fin putstr fd\n");
		t_allcmd++;
		// i++;
		// dprintf(2, "status all cmd %p, i:%d\n", t_allcmd, i);
	}
		ft_putstr_fd("\n", 1);
	// dprintf(2, "allcmd:%s, arg:%s, i:%d\n", *allcmd, (*t_allcmd) - 1, i);
	// dprintf(2, "hello\n");
}

void	ft_echowtopt(char **allcmd)
{
	char	**t_allcmd;

	t_allcmd = allcmd + 2;
	while (*t_allcmd != NULL)
	{
		// printf("%s", *t_allcmd);
		// fflush(stdout);
		ft_putstr_fd(*t_allcmd, 1);
		t_allcmd++;
	}
}
