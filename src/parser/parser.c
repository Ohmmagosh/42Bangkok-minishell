/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:52:55 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/14 22:30:25 by psuanpro         ###   ########.fr       */
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

void	create_cmd_parser(t_pro *p, t_llst *lst)
{
	int	i;

	i = 0;
	p->par.size = len_pipe(p->lex.lst);
	p->par.cmd = (t_cmd *)malloc(sizeof(t_cmd) * p->par.size);
	if (!p->par.cmd)
		return ;
	while (i < p->par.size)
	{
		while (lst != NULL)
		{
			printf("lst->content -> %s\n", lst->content);
			lst = lst->next;
		}
		i++;
	}
}

void	parser(t_pro *p)
{
	create_cmd_parser(p, p->lex.lst);
}

