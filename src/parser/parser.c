/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:52:55 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/17 22:04:59 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/fcntl.h>

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
	new.allcmd = get_allcmd(p, len);
	if (new.allcmd[0] != NULL)
		new.cmd = new.allcmd[0];
	return (new);
}

t_llst	*next_cmd(t_llst *lst)
{
	while (lst->next != NULL && ft_strncmp(lst->content, "|", 2))
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

void	print_chk_cmd(t_pro	*p)
{
	int	i = 0;
	int	j = 0;
	while (i < p->par.size)
	{
		printf("index %d\n",p->par.cmd[i].index);
		printf("cmd 1 %s\n", p->par.cmd[i].cmd);
		j = 0;
		printf("-----------all cmd------------\n");
		while (p->par.cmd[i].allcmd[j])
		{
			printf("%d %s\n", j,p->par.cmd[i].allcmd[j]);
			j++;
		}
		i++;
	}
}

char	*chk_opt(char **s)
{
	char	*ret;
	int		len;

	ret = NULL;
	len = 0;
	while (s[len])
		len++;
	if (len >= 2)
	{
		// if (s[1][0] == '-')
	}


	return (ret);
}

int	open_file_utils(char *file, int fd, int mode)
{
	close(fd);
	if (mode == 0)
	{
		fd = open(file, O_RDWR, 0644);
		if (fd == -1)
			fd = open(file,  O_CREAT | O_RDWR , 0644);
	}
	else if (mode == 1)
	{
		fd = open(file, O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			fd = open(file, O_CREAT | O_RDWR| O_TRUNC, 0644);
	}
	else if (mode == 2)
	{
		fd = open(file, O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			fd = open(file, O_CREAT | O_RDWR| O_APPEND, 0644);
	}
	return (fd);
}

int	open_file(char *file, int fd, int mode)
{
	if (fd == -1)
	{
		if (mode == 0)
		{
			fd = open(file, O_RDWR, 0644);
			if (fd == -1)
				fd = open(file,  O_CREAT | O_RDWR , 0644);
		}
		else if (mode == 1)
		{
			fd = open(file, O_RDWR | O_TRUNC, 0644);
			if (fd == -1)
				fd = open(file, O_CREAT | O_RDWR| O_TRUNC, 0644);
		}
		else if (mode == 2)
		{
			fd = open(file, O_RDWR | O_TRUNC | O_APPEND , 0644);
			if (fd == -1)
				fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		}
	}
	else if (fd != -1)
		fd = open_file_utils(file, fd, mode);
	return (fd);
}

t_ifd	chk_redirect(char **s)
{
	t_ifd	new;
	int		i;

	i = 0;
	new.infd = -1;
	new.outfd = -1;
	while (s[i])
	{
		if (!ft_strncmp(s[i], "<", 2))
			new.infd = open_file(s[i + 1], new.infd, 0);
		else if (!ft_strncmp(s[i], ">", 2))
			new.outfd = open_file(s[i + 1], new.outfd, 1);
		else if (!ft_strncmp(s[i], ">>", 3))
			new.outfd = open_file(s[i + 1], new.outfd, 2);
		i++;
	}
	return (new);
}

void	add_redirect(t_pro *p)
{
	int	i;

	i = 0;
	while (i < p->par.size)
	{
		p->par.cmd[i].re = chk_redirect(p->par.cmd[i].allcmd);
		i++;
	}
}
int	chk_meta_str(char *s)
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

int	error_redi(char **s)
{
	int	i;
	int	ret;

	i = 0;
	while (s[i])
	{
		if (chk_meta_str(s[1]) && chk_meta_str(s[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	chk_error_redirect(t_pro *p)
{
	int	status;
	int	i;
	int	j;

	i = 0;
	status = 1;
	while (i < p->par.size)
	{
		if (status == 0)
			break;
		status = error_redi(p->par.cmd[i].allcmd);
		i++;
	}
	return (status);
}

void	add_opt_cmd(t_pro *p)
{
	int	i;
	char	*tmp;

	i = 0;

	while (i < p->par.size)
	{

		p->par.cmd[i].option = chk_opt(p->par.cmd[i].allcmd);
		i++;
	}
}

void	parser(t_pro *p)
{
	create_cmd_parser(p, p->lex.lst);
	if (!chk_error_redirect(p))
	{
		add_redirect(p);
		add_opt_cmd(p);
	}
	// print_chk_cmd(p);
}
