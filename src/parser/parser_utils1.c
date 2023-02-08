/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:30:07 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 07:31:08 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*file_name_here_doc(int	idx, int cmd)
{
	char	*name;
	char	*name_tmp;
	char	*index;
	char	*index_cmd;

	index = ft_itoa(idx);
	index_cmd = ft_itoa(cmd);
	name_tmp = ft_strdup("here_doc_");
	name = ft_strjoin(name_tmp, index_cmd);
	free(name_tmp);
	free(index_cmd);
	name_tmp = ft_strjoin(name, index);
	free(name);
	free(index);
	return (name_tmp);
}

int	here_doc_utils(char *name, char *eof)
{
	char	*line;
	int		fd;
	int		len;

	fd = open(name, O_CREAT | O_RDWR | O_APPEND , 0777);
	len = ft_strlen(eof);
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (!ft_strncmp(line, eof, len))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (fd);
}


int	ismeta(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

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
