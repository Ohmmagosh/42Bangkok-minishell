/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:52:55 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/31 00:42:41 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_opt(char *s)
{
	char	*ret;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == '-')
			len++;
		i++;
	}
	if (len != 1)
		return ft_calloc(1, 1);
	else
		ret = ft_strdup(s);
	return (ret);
}

int	next_cmd(char **cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (!ft_strncmp(cmd[j], "|", 2) || cmd[j] == NULL)
			break;
		j++;
	}
	return (j);
}

t_cmd	parser_cmd_util(char **cmd, int end, int id)
{
	t_cmd	*new;
	int		i;

	i = 0;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	new->index = id;
	new->allcmd = (char **)malloc(sizeof(char *) * (end + 1));
	new->cmd = ft_strdup(cmd[0]);
	new->option = get_opt(cmd[1]);
	while (i < end)
	{
		if (cmd[i] == NULL)
			break;
		new->allcmd[i] = ft_strdup(cmd[i]);
		i++;
	}
	new->allcmd[end] = NULL;
	return (*new);
}


t_par	init_parser_cmd(t_par par, char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	par.cmd = (t_cmd *)malloc(sizeof(t_cmd) * par.size);
	while (i < par.size)
	{
		par.cmd[i] = parser_cmd_util(&cmd[j], next_cmd(&cmd[j]), i);
		j += next_cmd(&cmd[j]) + 1;
		i++;
	}
	return (par);
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
	p->par = init_parser_cmd(p->par, p->lex.split);
	for (int k = 0; k < p->par.size; k++)
	{
		printf("p->par.cmd[k].index -> %d\n", p->par.cmd[k].index);
		printf("p->par.cmd[k].opt -> %s\n", p->par.cmd[k].option);
		printf("par.cmd[k]->cmd -> %s\n", p->par.cmd[k].cmd);
		for (int n = 0; p->par.cmd[k].allcmd[n]; n++)
			printf("par.cmd[k].allcmd[n] -> %s\n", p->par.cmd[k].allcmd[n]);
		printf("%s--------------------%s\n", "\e[42m", "\e[0m");
	}
	printf("p->par.size -> %d\n", p->par.size);
	
	return ;
}
