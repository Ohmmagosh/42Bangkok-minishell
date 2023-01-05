/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:17:41 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/31 15:49:25 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_pro	p;

	while (1)
	{
		p.lex.cmd = readline("\e[0;102mminishell->>\033[0m");
		if (ft_strncmp(p.lex.cmd, "exit\0", 6) == 0)
		{
			ft_putendl_fd("exit", 1);
			free(p.lex.cmd);
			exit(0);
		}
		lexer(&p);
		parser(&p);
	}
	return 0;
}
