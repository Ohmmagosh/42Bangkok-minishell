/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:52:55 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 07:34:29 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	new_str_len(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if(ft_strncmp(str[i], "", 1))
			len++;
		i++;
	}
	return (len);
}

char	**new_str_utils(char **str)
{
	char	**ret;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = new_str_len(str);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if(ft_strncmp(str[i], "", 1))
		{
			ret[j] = ft_strdup(str[i]);
			j++;
		}
		i++;
	}
	ret[j] = NULL;
	return (ret);
}

char	**new_str(char **cmd)
{
	int	i;
	char	**ret;

	i = 0;
	ret = NULL;
	while (cmd[i] && cmd[i])
	{
		if (ismetastr(cmd[i]) && cmd[i])
		{
			cmd[i] = newrealloc(cmd[i]);
			if (cmd[i + 1])
				cmd[i + 1] = newrealloc(cmd[i + 1]);
		}
		i++;
	}
	i = 0;
	ret = new_str_utils(cmd);
	free_split(cmd);
	return (ret);
}

void	chk_redirect(t_pro *p)
{
	int	i;

	i = 0;
	while (i < p->par.size)
	{
		if(!chk_redirect_cmd(p->par.cmd[i].allcmd))
			p->par.cmd[i].error = ft_strdup("token\n");
		while (p->par.cmd[i].error == NULL)
		{
			get_redirect_fd(&p->par.cmd[i], p->par.cmd[i].allcmd);
		}
		i++;
	}
	i = 0;
	while (i < p->par.size)
	{
		p->par.cmd[i].allcmd = new_str(p->par.cmd[i].allcmd);
		i++;
	}
}

void	parser(t_pro *p)
{
	create_cmd_parser(p, p->lex.lst);
	chk_redirect(p);
}

