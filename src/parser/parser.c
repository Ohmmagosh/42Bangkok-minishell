/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:52:55 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/14 23:44:36 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_lst(t_llst *p)
{
	while (p)
	{
		printf("p->content -> |%s|\n", p->content);
		p = p->next;
	}
}

int	len_pipe(t_llst *p)
{
	int	len;

	len = 0;
	while (p)
	{
		if (!ft_strncmp(p->content, "|", 2))
			len++;
		p = p->next;
	}
	return (len + 1);
}

int	len_cmd_parser(t_llst *p)
{
	int	len;

	while (p != NULL && ft_strncmp(p->content, "|", 2))
	{
		len++;
		p = p->next;
	}
	return (len);
}

char	**get_allcmd(t_llst *lst, int size)
{
	char	**ret;
	int		i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	while (lst && i < size)
	{
		ret[i] = ft_strdup(lst->content);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

t_cmd	init_cmd_parser(t_llst *p, int idx)
{
	t_cmd	new;
	int		len;

	len = len_cmd_parser(p);
	new.index = idx;
	new.allcmd = get_allcmd(p, len);

	return (new);
}

void	create_cmd_parser(t_pro *p, t_llst *lst)
{
	int	i;

	i = 0;
	p->par.size = len_pipe(p->lex.lst);
	p->par.cmd = (t_cmd *)malloc(sizeof(t_cmd) * p->par.size);
	if (!p->par.cmd)
		return ;
	while (lst && i < p->par.size)
	{
		if (!ft_strncmp(lst->content, "|", 2))
			i++;

		p->par.cmd[i] = init_cmd_parser(lst, i);
		lst = lst->next;
	}
}

void	parser(t_pro *p)
{
	create_cmd_parser(p, p->lex.lst);
}

