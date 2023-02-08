/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:30:10 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 07:49:42 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_cmd_allcmd(t_llst *lst)
{
	int	len;

	len = 0;
	while (lst && ft_strncmp(lst->content, "|", 2))
	{
		len++;
		lst = lst->next;
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
		lst = lst->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

t_cmd	init_cmd_parser(t_llst *p, int idx)
{
	t_cmd	new;
	int		len;

	len = len_cmd_allcmd(p);
	new.index = idx;
	new.error = NULL;
	new.re.infd = 0;
	new.re.outfd = 1;
	new.heredoc = NULL;
	new.allcmd = get_allcmd(p, len);
	if (new.allcmd[0] != NULL)
		new.cmd = new.allcmd[0];
	return (new);
}

t_llst	*next_cmd(t_llst *lst)
{
	while (lst && lst->next != NULL && ft_strncmp(lst->content, "|", 2))
		lst = lst->next;
	if (!ft_strncmp(lst->content, "|", 2) && lst != NULL)
		lst = lst->next;
	return (lst);
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
		p->par.cmd[i] = init_cmd_parser(lst, i);
		lst = next_cmd(lst);
		i++;
	}
}
