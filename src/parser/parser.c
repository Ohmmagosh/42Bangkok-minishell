/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:52:55 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/28 11:46:28 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	next_lst(char **cmd, int len)
{
	
}

void	first_lst(char **cmd, int len)
{
	t_lst	*new;
	
}

int	len_pipe(char **cmd)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "|", 2))
			len++;
		i++;
	}
	return (len);
}

t_lst	*create_lst(char **cmd)
{
	t_lst	*ret;
	int j = 0;

	ret = NULL;
	while (cmd[j])
	{
		if (!ft_strncmp(cmd[j], "|", 2))
			j++;
		else
			printf("cmd[%d] -> %s\n", j, cmd[j]);
		j++;
	}
	return (ret);
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
	
	
	// for (int j = 0; p->lex.split[j]; j++)
	// 	printf("p->lex.split[%d] -> |%s|\n", i, p->lex.split[j]);
	// p->par.lst = create_lst(p->lex.split);
	printf("len_pipe(p->lex.split) -> %d\n", len_pipe(p->lex.split));
	// for (int j = 0; condition; inc-expression) {
	
	// }
	return;
}