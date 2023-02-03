/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:46:05 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/01 23:31:54 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echonoopt(char **allcmd)
{
	char	**t_allcmd;

	t_allcmd = allcmd + 1;
	while (*t_allcmd != NULL)
	{
		printf("%s\n", *t_allcmd);
		t_allcmd++;
	}
}

void	ft_echowtopt(char **allcmd)
{
	char	**t_allcmd;

	t_allcmd = allcmd + 2;
	while (*t_allcmd != NULL)
	{
		printf("%s", *t_allcmd);
		t_allcmd++;
	}
}
