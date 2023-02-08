/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:30:17 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 07:32:51 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_heredoc(t_cmd *p, char *eof, int i)
{
	char	*name;

	name = file_name_here_doc(i, p->index);
	if (p->re.outfd != 1)
		close(p->re.infd);
	if (p->heredoc != NULL)
	{
		unlink(p->heredoc);
		free(p->heredoc);
		p->heredoc = NULL;
	}
	p->re.infd = here_doc_utils(name, eof);
	p->heredoc = ft_strdup(name);
	free(name);
	name = NULL;
	return (1);
}

void	get_redirect_fd_utils0(t_cmd *p, int *i)
{
	(*i) = 0;
	p->re.infd = 0;
	p->re.outfd = 1;
}

void	get_redirect_fd_utils1(t_cmd *p, int *i, char **cmd)
{
	if (!ft_strncmp(cmd[(*i)], "<", 2))
	{
		if (!get_infile(p, cmd[(*i) + 1], (*i)))
			p->error = ft_strdup("nfile");
	}
	else if (!ft_strncmp(cmd[(*i)], "<<", 2))
	{
		if(!get_heredoc(p, cmd[(*i) + 1], (*i)))
			p->error = ft_strdup("nfile");
	}
	else if (!ft_strncmp(cmd[(*i)], ">", 2))
	{
		if (!get_outfile(p, cmd[(*i) + 1], (*i)))
			p->error = ft_strdup("nfile");
	}
	else if (!ft_strncmp(cmd[(*i)], ">>", 2))
	{
		if (!get_append(p, cmd[(*i) + 1], (*i)))
			p->error = ft_strdup("nfile");
	}
}

void	get_redirect_fd(t_cmd *p, char **cmd)
{
	int		i;

	get_redirect_fd_utils0(p, &i);
	while (cmd[i] && cmd[i + 1])
	{
		get_redirect_fd_utils1(p, &i, cmd);
		i++;
	}
	if (p->error == NULL)
		p->error = ft_strdup("stop");
}

char	*newrealloc(char *s)
{
	free(s);
	s = ft_calloc(1, 1);
	return (s);
}
