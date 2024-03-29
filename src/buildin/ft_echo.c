/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:46:05 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/07 19:59:20 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

void	ft_echonoopt(char **allcmd)
{
	char	**t_allcmd;

	t_allcmd = allcmd + 1;
	while (*t_allcmd != NULL)
	{
		ft_putstr_fd(*t_allcmd, 1);
		if ((t_allcmd + 1) != NULL)
			ft_putstr_fd(" ", 1);
		t_allcmd++;
	}
	ft_putstr_fd("\n", 1);
}

void	ft_echowtopt(char **allcmd)
{
	char	**t_allcmd;

	t_allcmd = allcmd + 2;
	while (*t_allcmd != NULL)
	{
		ft_putstr_fd(*t_allcmd, 1);
		t_allcmd++;
	}
}
