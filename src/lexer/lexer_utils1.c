/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:06:29 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 20:23:38 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_llst	*create_head(char *s)
{
	t_llst	*new;

	new = (t_llst *)malloc(sizeof(t_llst));
	if (!new)
		return (perror("lexer : malloc error\n"), (t_llst *) NULL);
	new->content = ft_strdup(s);
	new->next = NULL;
	return (new);
}

void	create_next(t_llst *lst, char *s)
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
	s = NULL;
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

	if (s[0] == '\"' && s[ft_strlen(s) - 1] == '\"')
		tmp = ft_strtrim(s, "\"");
	else if (s[0] == '\'' && s[ft_strlen(s) - 1] == '\'')
		tmp = ft_strtrim(s, "\'");
	free(s);
	return (tmp);
}
