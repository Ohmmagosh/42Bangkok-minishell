/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:46:05 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/29 21:13:13 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echonoopt(char **allcmd)
{
	char	**t_allcmd;
	
	t_allcmd = allcmd + 1;
	while (*t_allcmd != NULL)
	{
		printf("all cmd:%s\n", *t_allcmd);
		t_allcmd++;
	}
	exit(0);
}

void	ft_echowtopt(char **allcmd)
{
	char	**t_allcmd;
	
	t_allcmd = allcmd + 2;
	while (*t_allcmd != NULL)
	{
		printf("all cmd:%s", *t_allcmd);
		t_allcmd++;
	}
	exit(0);
}