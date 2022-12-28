/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:52:55 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/29 00:44:42 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <malloc/_malloc.h>
#include <stdio.h>

// int	len_cmd(char **cmd)
// {
// 	int	ret;
// 	int	i;

// 	i = 0;
// 	ret = 0;
// 	while (cmd[i])
// 	{
// 		if (!ft_strncmp(cmd[i], "|", 2))
// 			ret++;
// 		i++;
// 	}	
// 	return (ret);
// }

// void	next_lst(t_lst **lst, char **cmd)
// {
// 	t_lst	*new;

// 	new = (t_lst *)malloc(sizeof(t_lst));
// 	if (!new)
// 		return ;

// }

// t_lst	*first_lst(char **cmd)
// {
// 	t_lst	*new;

// 	new = (t_lst *)malloc(sizeof(t_lst));
// 	if (!new)
// 		return (NULL);
	
	
// }
void	init_parser(t_lst *par)
{
	par->cmd = NULL;
	par->allcmd = NULL;
	par->option = NULL;
}

int	len_pipe(char **cmd)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "|", 2) && cmd[i + 1] != NULL)
			len++;
		i++;
	}
	return (len + 1);
}



char	*trim_split(char *s)
{
	char	*ret;

	ret = ft_strtrim(s, " \t");
	free(s);
	return (ret);
}

void	parser(t_pro *p)
{
	int	i;

	i = -1;
	while (p->lex.split[++i])
		p->lex.split[i] = trim_split(p->lex.split[i]);
	p->par.size = len_pipe(p->lex.split);
	p->par.lst = (t_lst *)malloc(sizeof(t_lst) * (p->par.size));
	i = 0;
	while (i < p->par.size)
	{
		p->par.lst[i] = init_parser(p->par.lst[i]);
	}

	
	
	return;
}
