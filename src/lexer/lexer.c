/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:12:13 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/15 23:19:20 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lexer(t_pro *p)
{
	p->lex.split = ft_split(p->lex.cmd, ' ');
	free(p->lex.cmd);
	
	printf("------------------------\n");
	for (int i = 0; p->lex.split[i]; i++)
		printf("  split[%d] %s", i, p->lex.split[i]);
	printf("\n");
}



// void	ft_echo(char *s)
// {
// 	printf("%s", s);
// }