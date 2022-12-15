/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:17:41 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/15 01:47:07 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	main(void)
{
	t_pro	p;

	while (1)
	{
		p.lex.cmd = readline("readline->");
		if (ft_strncmp(p.lex.cmd, "exit", 5) == 0)
		{
			free(p.lex.cmd);
			exit(0);
		}
		// rl_replace_line("", 0);
		lexer(&p);
		parser(&p);
	//	printf("->%s\n", p.hello);
		// printf("sig %d\n", sigaction(p.lex.cmd));
	}
	return 0;
}
// void    ft_tokenprint(t_token *token, int mode, char *color)
// {
//     t_token    *tmp;

//     tmp = token;
//     //printf("%d\n", mode);
//     while (tmp && (mode-- || mode == -1))
//     {
//         printf("%s<================================================>%s\n", color,C_RESET);
//         printf("%s<= Token\t:\t]%s[\t\t\t=>%s\n", color, tmp->token, C_RESET);
//         printf("%s<= Type\t\t:\t]%d[\t\t\t=>%s\n", color, tmp->type,C_RESET);
//         printf("%s<= Quote type\t:\t]%d[\t\t\t=>%s\n", color, tmp->quote,C_RESET);
//         printf("%s<= Prev Addr\t:\t]%-14p[\t=>%s\n", color, tmp->prev,C_RESET);
//         printf("%s<= Current Addr\t:\t]%-14p[\t=>%s\n", color, tmp,C_RESET);
//         printf("%s<= Next Addr\t:\t]%-14p[\t=>%s\n", color, tmp->next,C_RESET);
//         printf("%s<================================================>%s\n", color,C_RESET);
//         printf("\n");
//         tmp = tmp->next;
//     }
// }	