/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:12:13 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/17 01:00:19 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lexer(t_pro *p)
{
	p->lex.trim = ft_strtrim(p->lex.cmd, " ");
	printf("trim |%s|\n", p->lex.trim);

	p->lex.cut = (t_lst *)malloc(sizeof(t_lst));
		
	// lexer_split(p->lex.trim);
	// if (!p->lex.trim)
	// 	free(p->lex.trim);

	
	// printf("------------------------\n");
	// for (int i = 0; p->lex.split[i]; i++)
	// 	printf("  split[%d] %s", i, p->lex.split[i]);
	// printf("\n");
}



// void	ft_echo(char *s)
// {
// 	printf("%s", s);
// }