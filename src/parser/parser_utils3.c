/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:30:12 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 07:32:29 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ismetastr(char *s)
{
	if (s == NULL)
		return (0);
	if (!ft_strncmp(s, "<", 2))
		return (1);
	else if(!ft_strncmp(s, ">", 2))
		return (1);
	else if(!ft_strncmp(s, "|", 2))
		return (1);
	else if (!ft_strncmp(s, "<<", 3))
		return (1);
	else if (!ft_strncmp(s, ">>", 3))
		return (1);
	return (0);
}

int	chk_redirect_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i + 1])
	{
		if (ismetastr(cmd[i]) && ismetastr(cmd[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	get_append(t_cmd *p, char *file, int ot)
{
	if (ot > 0 && p->re.outfd != 1)
		close(p->re.outfd);
	p->re.infd = open(file, O_RDWR | O_APPEND);
	if (p->re.outfd == -1)
	{
		p->re.outfd = open(file, O_CREAT| O_RDWR | O_APPEND, 0644);
		if (p->re.outfd == -1)
			return (0);
	}
	return (1);
}

int	get_infile(t_cmd *p,char *file, int ot)
{
	if (ot > 0 && p->re.infd != 0)
		close(p->re.infd);
	p->re.infd = open(file, O_RDONLY);
	if (p->re.infd == -1)
		return (0);
	return (1);
}

int	get_outfile(t_cmd *p, char *file ,int ot)
{
	if (ot > 0 && p->re.outfd != 1)
		close(p->re.outfd);
	p->re.outfd = open(file, O_RDWR| O_TRUNC);
	if (p->re.outfd == -1)
	{
		p->re.outfd = open(file, O_CREAT| O_RDWR| O_TRUNC, 0644);
		if (p->re.outfd == -1)
			return (0);
	}
	return (1);
}
