/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:17:41 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/14 22:20:30 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_pro	p;

	while (1)
	{
		// p.prompt = init_prompt();
		p.lex.cmd = readline("\e[0;102mminishell->>\033[0m");
		add_history(p.lex.cmd);
		if (ft_strncmp(p.lex.cmd, "exit\0", 6) == 0)
		{
			ft_putendl_fd("exit", 1);
			free(p.lex.cmd);
			exit(0);
		}
		lexer(&p);
		if (p.lex.status)
			parser(&p);
	}
	return 0;
}
