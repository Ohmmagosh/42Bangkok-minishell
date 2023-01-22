/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:12:13 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/23 00:29:21 by psuanpro         ###   ########.fr       */
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

void	lexer_lst(t_pro *p, char *s)
{
	int		i;
	char	*stack;
	char	*quote;

	i = 0;
	p->lex.lst = NULL;
	stack = ft_calloc(1, 1);
	if (!stack)
		return ;
	while (s[i])
	{
		if (s[i] == '\"')
		{
			stack = join_char(stack, s[i]);
			i++;
			while (s[i] != '\"')
			{
				if (s[i] == '\0')
				{
					print_error(p, "\e[1;91mError lexer\e[0m");
					break;
				}
				stack = join_char(stack, s[i]);
				i++;
			}
			stack = join_char(stack, s[i]);
			i++;
		}
		else if (s[i] == '\'')
		{
			stack = join_char(stack, s[i]);
			i++;
			while (s[i] != '\'')
			{
				if(s[i] == '\0')
				{
					print_error(p, "\e[1;91mError lexer\e[0m");
					break;
				}
				stack = join_char(stack, s[i]);
				i++;
			}
			stack = join_char(stack, s[i]);
			i++;
		}
		else if (s[i] == '>' && s[i + 1] == '>')
		{
			create_linklst(p, ">>");
			i += 2;
			while (s[++i] == ' ')
				;
		}
		else if (s[i] == '<' && s[i + 1] == '<')
		{
			create_linklst(p, "<<");
			i += 1;
			while (s[++i] == ' ')
				;
		}
		else if (s[i] == '<')
		{
			create_linklst(p, "<");
			while (s[++i] == ' ')
				;
		}
		else if (s[i] == '>')
		{
			create_linklst(p, ">");
			while (s[++i] == ' ')
				;
		}
		else if (s[i] == '|' && s[i + 1] != '<' && s[i + 2] != '<')
		{
			create_linklst(p, "|");
			while (s[++i] == ' ')
				;
		}
		else if (s[i] == '|' && s[i + 1] == '<' && s[i + 2] == '<')
		{
			create_linklst(p, "|");
			create_linklst(p, "<<");
			i += 3;
			while (s[++i] == ' ')
				;
		}
		else if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '|')
		{
			create_linklst(p, "<<");
			create_linklst(p, "|");
			i += 3;
			while (s[++i] == ' ')
				;
		}
		else if (s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i + 1] != '>' && s[i + 1] != '<' && !ft_isalnum(s[i]))
		{
			stack = join_char(stack, s[i]);
			i++;
		}
		else if (ft_isalnum(s[i]))
		{
			stack = join_char(stack, s[i]);
			i++;
		}
		if (s[i] == ' ' || s[i] == '\0' || s[i] == '|'|| s[i] == '<' || s[i] == '>')
		{
			create_linklst(p, stack);
			stack = ft_calloc(1, 1);
			if (s[i] == ' ')
				i++;
		}
	}
	free(stack);
}

void	lexer(t_pro *p)
{
	p->lex.status = 1;
	p->lex.trim = ft_strtrim(p->lex.cmd, " ");
	free(p->lex.cmd);
	lexer_lst(p, p->lex.trim);
	free(p->lex.trim);
}
