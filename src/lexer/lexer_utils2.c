/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:07:14 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 07:07:39 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_error(t_pro *p, char *s)
{
	p->lex.status = 0;
	ft_putendl_fd(s, 2);
}

void	double_quote(t_pro *p, char *s, int *i)
{
	p->lex.stack = join_char(p->lex.stack, s[(*i)]);
		(*i)++;
	while (s[(*i)] != '\"')
	{
		if (s[(*i)] == '\0')
		{
			print_error(p, "\e[1;91mError lexer\e[0m");
			break;
		}
		p->lex.stack = join_char(p->lex.stack, s[(*i)]);
		(*i)++;
	}
	p->lex.stack = join_char(p->lex.stack, s[(*i)]);
	(*i)++;
}

void	single_quoate(t_pro *p, char *s, int *i)
{
	p->lex.stack = join_char(p->lex.stack, s[(*i)]);
		(*i)++;
	while (s[(*i)] != '\'')
	{
		if(s[(*i)] == '\0')
		{
			print_error(p, "\e[1;91mError lexer\e[0m");
			break;
		}
		p->lex.stack = join_char(p->lex.stack, s[(*i)]);
		(*i)++;
	}
	p->lex.stack = join_char(p->lex.stack, s[(*i)]);
	(*i)++;
}

void	plus_i(int *i, char c, char *s)
{
	while (s[++(*i)] == c)
		;
}

void	repipe(t_pro *p, int *i, char *s, int mode)
{
	if (mode == 0)
	{
		create_linklst(p, "<<");
		create_linklst(p, "|");
		(*i) += 3;
		plus_i(i, ' ', s);
	}
	else if (mode == 1)
	{
		create_linklst(p, "|");
		create_linklst(p, "<<");
		(*i) += 3;
		plus_i(i, ' ', s);
	}
}
