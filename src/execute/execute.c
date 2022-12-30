/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:46:22 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/31 02:39:09 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute(t_pro *p)
{
	int	fd[2];
	int	pid;
	int	i;

	i = 0;
	while (i < lencmd)
	{
		pid = fork(fd);
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			//child
		}
		else {
			//parent
		}
		return ;
	}
}