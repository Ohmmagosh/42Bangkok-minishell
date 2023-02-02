/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:12:13 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/01 21:31:08 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_llst	*create_head(char *s)
{
	t_llst	*new;

	new = (t_llst *)malloc(sizeof(t_llst));
	if (!new)
		return (perror("lexer : malloc error\n"), (t_llst *)NULL);
	new->content = ft_strdup(s);
	new->next = NULL;
	return (new);
}

void	create_next(t_llst	*lst, char *s)
{
	t_llst	*new;

	new = (t_llst *)malloc(sizeof(t_llst));
	if (!new)
		return ;
	while (lst->next != NULL)
		lst = lst->next;
	new->content = ft_strdup(s);
	new->next = NULL;
	lst->next = new;
}

char	*join_char(char *s, char c)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (c)
		len = 1 ;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + len + 1));
	if (!ret)
		return (NULL);
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	free(s);
	return (ret);
}

void	create_linklst(t_pro *p, char *s)
{
	if (s[0] == '\0')
		return ;
	if (!p->lex.lst)
		p->lex.lst = create_head(s);
	else
		create_next(p->lex.lst, s);
}


char	*subtrim(char *s)
{
	char	*tmp;

	if(s[0] == '\"' && s[ft_strlen(s) - 1] == '\"')
		tmp = ft_strtrim(s, "\"");
	else if(s[0] == '\'' && s[ft_strlen(s) - 1] == '\'')
		tmp = ft_strtrim(s, "\'");
	free(s);
	return (tmp);
}

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
		i += 3;
		plus_i(i, ' ', s);
	}
}

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
		i += 1;
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
	if (!p->lex.stack)
		return ;
}

void	lexer_lst_utils(t_pro *p, char *s, int *i)
{
	if (s[(*i)] == '|' && s[(*i) + 1] == '<' && s[(*i) + 2] == '<')
			repipe(p, i, s, 0);
	else if (s[(*i)] == '<' && s[(*i) + 1] == '<' && s[(*i) + 2] == '|')
		repipe(p, i, s, 0);
	else if (s[(*i)] != '|' && s[(*i)] != '<' && s[(*i)] != '>' && s[(*i) + 1] != '>'\
		&& s[(*i) + 1] != '<' && !ft_isalnum(s[(*i)]))
		join_char_utils(p, s, i);
	else if (ft_isalnum(s[(*i)]))
		join_char_utils(p, s, i);
	if (s[(*i)] == ' ' || s[(*i)] == '\0' || s[(*i)] == '|'|| s[(*i)] == '<' || s[(*i)] == '>')
	{
		create_linklst(p, p->lex.stack);
		p->lex.stack = ft_calloc(1, 1);
		if (s[(*i)] == ' ')
			(*i)++;
	}
}

void	lexer_lst(t_pro *p, char *s)
{
	int		i;

	lexer_init(p, &i);
	while (s[i])
	{
		if (s[i] == '\"')
			double_quote(p, s, &i);
		else if (s[i] == '\'')
			single_quoate(p, s, &i);
		else if (s[i] == '>' && s[i + 1] == '>' || s[i] == '<' && s[i + 1] == '<')
			appendheredoc(p, s, &i);
		else if (s[i] == '<' || s[i] == '>')
			redi(p, &i, s);
		else if (s[i] == '|' && s[i + 1] != '<' && s[i + 2] != '<')
		{
			create_linklst(p, "|");
			plus_i(&i, ' ', s);
		}
		else
			lexer_lst_utils(p, s, &i);
	}
	free(p->lex.stack);
}

void	lexer(t_pro *p)
{
	p->lex.status = 1;
	p->lex.trim = ft_strtrim(p->lex.cmd, " ");
	free(p->lex.cmd);
	lexer_lst(p, p->lex.trim);
	free(p->lex.trim);
}
