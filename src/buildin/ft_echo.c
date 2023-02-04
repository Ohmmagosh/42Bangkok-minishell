/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:46:05 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/04 23:10:58 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void	ft_echonoopt(char **allcmd)
{
	char	**t_allcmd;

	t_allcmd = allcmd + 1;
	while (*t_allcmd != NULL)
	{
		ft_putstr_fd(*t_allcmd, 1);
		ft_putstr_fd("\n", 1);
		t_allcmd++;
	}
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
