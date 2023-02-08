/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:07:56 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 07:08:05 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	join_char_utils(t_pro *p, char *s, int *i)
{
	p->lex.stack = join_char(p->lex.stack, s[(*i)]);
	(*i)++;
}

void	redi(t_pro *p, int *i, char *s)
{
	if (s[(*i)] == '<')
		create_linklst(p, "<");
	else if (s[(*i)] == '>')
		create_linklst(p, ">");
	plus_i(i, ' ', s);
}

void	appendheredoc(t_pro *p,char *s, int *i)
{
	if (s[(*i)] == '>' && s[(*i) + 1] == '>')
	{
		create_linklst(p, ">>");
		(*i) += 1;
	}
	else if (s[(*i)] == '<' && s[(*i) + 1] == '<')
		create_linklst(p, "<<");
	(*i) += 1;
	plus_i(i, ' ', s);
}

void	lexer_init(t_pro *p, int *i)
{
	(*i) = 0;
	p->lex.lst = NULL;
	p->lex.stack = ft_calloc(1, 1);
}

int	lexer_lst_utils1(char *s, int i)
{
	if (s[i] == '|' && s[i + 1] != '<' && s[i + 2] != '<')
		return (1);
	else if (s[i] == '|' && s[i + 1] == '<' && s[i + 2] == '<')
		return (1);
	else if(s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '|')
		return (1);
	else if(s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i + 1] != '>' && s[i + 1] != '<' && !ft_isalnum(s[i]))
		return (1);
	else if(ft_isalnum(s[i]))
		return (1);
	return (0);
}
