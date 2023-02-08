/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:12:13 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 07:43:37 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lexer_lst_utils0(t_pro *p, int *i, char *s)
{
	if (s[(*i)] == '<' || s[(*i)] == '>')
		redi(p, i, s);
	else if (s[(*i)] == '|' && s[(*i) + 1] != '<' && s[(*i) + 2] != '<')
	{
		create_linklst(p, "|");
		plus_i(i, ' ', s);
	}
	else if (s[(*i)] == '|' && s[(*i) + 1] == '<' && s[(*i) + 2] == '<')
		repipe(p, i, s, 0);
	else if (s[(*i)] == '<' && s[(*i) + 1] == '<' && s[(*i) + 2] == '|')
		repipe(p, i, s, 0);
	else if (s[(*i)] != '|' && s[(*i)] != '<' && s[(*i)] != '>' \
		&& s[(*i) + 1] != '>' && s[(*i) + 1] != '<' && !ft_isalnum(s[(*i)]))
		join_char_utils(p, s, i);
	else if (ft_isalnum(s[(*i)]))
		join_char_utils(p, s, i);
}

void	lexer_lst(t_pro *p, char *s)
{
	int	i;

	lexer_init(p, &i);
	while (s[i])
	{
		if (s[i] == '\"')
			double_quote(p, s, &i);
		else if (s[i] == '\'')
			single_quoate(p, s, &i);
		else if (s[i] == '>' && s[i + 1] == '>' || s[i] == '<' \
			&& s[i + 1] == '<')
			appendheredoc(p, s, &i);
		else if (lexer_lst_utils1(s, i))
			lexer_lst_utils0(p, &i, s);
		if (s[i] == ' ' || s[i] == '\0' || s[i] == '|' || s[i] == '<' \
			|| s[i] == '>')
		{
			create_linklst(p, p->lex.stack);
			p->lex.stack = ft_calloc(1, 1);
			if (s[i] == ' ')
				i++;
		}
	}
	free(p->lex.stack);
}

void	lexer(t_pro *p)
{
	p->lex.status = 1;
	p->lex.trim = ft_strtrim(p->lex.cmd, " ");
	free(p->lex.cmd);
	lexer_lst(p, p->lex.trim);
	while (p->lex.lst)
	{
		printf("p->lex.lst->content -> %s\n", p->lex.lst->content);
		p->lex.lst = p->lex.lst->next;
	}
	exit(0);
	free(p->lex.trim);
}
