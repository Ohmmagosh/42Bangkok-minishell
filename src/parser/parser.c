/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:52:55 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/22 23:09:17 by psuanpro         ###   ########.fr       */
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
	
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC , 700);
	while (1)
	{
		write(1, "heredoc->", 9);
		line = get_next_line(0);
		printf("eof -> |%s|\n", eof);
		printf("line -> |%s|\n", line);
		if (!ft_strncmp(line, eof, ft_strlen(eof)))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (fd);
}

// int	here_doc(int idx, char **cmd)
// {
// 	int		i;
// 	int		fd;
// 	char	*name;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (!ft_strncmp(cmd[i], "<<", 3))
// 		{
// 			name = file_name_here_doc(idx,);
// 			fd = here_doc_utils(name, cmd[i + 1]);
// 		}
// 		i++;
// 	}
// 	return (fd);
// }


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
	new.error = NULL;
	new.re.infd = -1;
	new.re.outfd = -1;
	new.heredoc = NULL;
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
		printf("-----------cmd %d------------\n", i);
		printf("p->par.cmd[i].re.infd -> %d\n", p->par.cmd[i].re.infd);
		printf("p->par.cmd[i].re.outfd -> %d\n", p->par.cmd[i].re.outfd);
		while (p->par.cmd[i].allcmd[j])
		{
			printf("%d %s\n", j,p->par.cmd[i].allcmd[j]);
			j++;
		}
		i++;
	}
}

// char	*chk_opt(char **s)
// {
// 	char	*ret;
// 	int		len;

// 	ret = NULL;
// 	len = 0;
// 	while (s[len])
// 		len++;
// 	if (len >= 2)
// 	{
// 		// if (s[1][0] == '-')
// 	}


// 	return (ret);
// }

// int	open_file_utils(char *file, int fd, int mode)
// {
// 	close(fd);
// 	if (mode == 0)
// 	{
// 		fd = open(file, O_RDWR, 0644);
// 		if (fd == -1)
// 			fd = open(file,  O_CREAT | O_RDWR , 0644);
// 	}
// 	else if (mode == 1)
// 	{
// 		fd = open(file, O_RDWR | O_TRUNC, 0644);
// 		if (fd == -1)
// 			fd = open(file, O_CREAT | O_RDWR| O_TRUNC, 0644);
// 	}
// 	else if (mode == 2)
// 	{
// 		fd = open(file, O_RDWR | O_TRUNC, 0644);
// 		if (fd == -1)
// 			fd = open(file, O_CREAT | O_RDWR| O_APPEND, 0644);
// 	}
// 	return (fd);
// }

// int	open_file(char *file, int fd, int mode)
// {
// 	if (fd == -1)
// 	{
// 		if (mode == 0)
// 		{
// 			fd = open(file, O_RDWR, 0644);
// 			if (fd == -1)
// 				fd = open(file,  O_CREAT | O_RDWR , 0644);
// 		}
// 		else if (mode == 1)
// 		{
// 			fd = open(file, O_RDWR | O_TRUNC, 0644);
// 			if (fd == -1)
// 				fd = open(file, O_CREAT | O_RDWR| O_TRUNC, 0644);
// 		}
// 		else if (mode == 2)
// 		{
// 			fd = open(file, O_RDWR | O_TRUNC | O_APPEND , 0644);
// 			if (fd == -1)
// 				fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
// 		}
// 	}
// 	else if (fd != -1)
// 		fd = open_file_utils(file, fd, mode);
// 	return (fd);
// }

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

// t_ifd	chk_redirect_file(char **s)
// {
// 	t_ifd	new;
// 	int		i;

// 	i = 0;
// 	new.infd = -1;
// 	new.outfd = -1;
// 	while (s[i])
// 	{
// 		if (!ft_strncmp(s[i], "<", 2))
// 			new.infd = open_file(s[i + 1], new.infd, 0);
// 		else if (!ft_strncmp(s[i], ">", 2))
// 			new.outfd = open_file(s[i + 1], new.outfd, 1);
// 		else if (!ft_strncmp(s[i], ">>", 3))
// 			new.outfd = open_file(s[i + 1], new.outfd, 2);
// 		i++;
// 	}
// 	return (new);
// }

// void	add_redirect(t_pro *p)
// {
// 	int	i;

// 	i = 0;
// 	while (i < p->par.size)
// 	{
// 		p->par.cmd[i].re = chk_redirect_file(p->par.cmd[i].allcmd);
// 		i++;
// 	}
// }


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

int	chk_redirect_outfile(t_cmd *p, char **cmd)
{
	int	i;
	int	time_open;

	i = 0;
	time_open = 0;
	p->re.outfd = -1;
	while (cmd[i] && cmd[i + 1])
	{
		if (!ft_strncmp(cmd[i], ">", 2))
		{
			if (time_open > 0 && p->re.outfd < 0)
				close(p->re.outfd);
			p->re.outfd = open(cmd[i + 1], O_RDWR| O_TRUNC);
			time_open++ ;
			if (p->re.outfd == -1)
			{
				p->re.outfd = open(cmd[i + 1], O_CREAT| O_RDWR| O_TRUNC, 0644);
				if (p->re.outfd == -1)
					return (0);
			}
		}
		i++;
	}
	return (1);
}
//error 1 error redirect error near unexpected token
//error 2 error No such file or directory
int	chk_redirect_infile(t_cmd *p, char **cmd)
{
	int	i;
	int	time_open;

	i = 0;
	time_open = 0;
	p->re.infd = -1;
	while (cmd[i] && cmd[i + 1])
	{
		if (!ft_strncmp(cmd[i], "<", 2))
		{
			if (time_open > 0 && p->re.infd == -1)
				close(p->re.infd);
			p->re.infd = open(cmd[i + 1], O_RDONLY);
			time_open++ ;
			if (p->re.infd == -1)
				return (0);
		}
		i++;
	}
	return (1);
}

int	chk_redirect_heredoc(t_cmd *p, char **cmd)
{
	int	i;
	int	time_open;
	char	*name;

	i = 0;
	time_open = 0;
	while (cmd[i] && cmd[i + 1])
	{
		if (!ft_strncmp(cmd[i], "<<", 3))
		{
			name = file_name_here_doc(i, p->index);
			p->heredoc = ft_strdup(name);
			p->re.outfd = here_doc_utils(name, cmd[i + 1]);
		}
		i++;
	}
	return (1);
}

// int	chk_redirect_append(t_cmd *p, char **cmd)
// {
// 	int	i;
// 	int	time_open;

// 	i = 0;
// 	time_open = 0;
// 	while (cmd[i] && cmd[i + 1])
// 	{
// 		if (!ft_strncmp(cmd[i], ">>", 3))
// 		{
// 			if (time_open > 0 && p->re.outfd == -1)
// 				close(p->re.outfd);
// 			p->re.infd = open(cmd[i + 1], O_RDWR | O_APPEND);
// 			time_open++ ;
// 			if (p->re.outfd == -1)
// 			{
// 				p->re.outfd = open(cmd[i + 1], O_CREAT| O_RDWR | O_APPEND, 0644);
// 				if (p->re.outfd == -1)
// 					return (0);
// 			}
// 		}
// 		i++;
// 	}
// 	return (1);
// }

int	get_append(t_cmd *p, char *file, int ot)
{
	if (ot > 0 && p->re.outfd != -1)
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
	if (ot > 0 && p->re.infd != -1)
		close(p->re.infd);
	p->re.infd = open(file, O_RDONLY);
	if (p->re.infd == -1)
		return (0);
	return (1);
}

int	get_outfile(t_cmd *p, char *file ,int ot)
{
	if (ot > 0 && p->re.outfd != -1)
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

int	get_heredoc(t_cmd *p, char *eof, int i)
{
	char	*name;
	
	name = file_name_here_doc(i, p->index);
	if (p->re.outfd != -1)
		close(p->re.infd);
	if (p->heredoc != NULL)
	{
		unlink(p->heredoc);
		free(p->heredoc);
		p->heredoc = NULL;
	}
	printf("%s----------heredoc----------%s\n", "\e[42m", "\e[0m");
	printf("eof -> %s\n", eof);
	p->re.infd = here_doc_utils(name, eof);
	free(name);
	return (1);
}

void	get_redirect_fd(t_cmd *p, char **cmd)
{
	int		i;

	i = 0;
	p->re.infd = -1;
	p->re.outfd = -1;
	while (cmd[i] && cmd[i + 1])
	{
		if (!ft_strncmp(cmd[i], "<", 2))
		{
			if (!get_infile(p, cmd[i + 1], i))
				p->error = ft_strdup("nfile");
		}
		else if (!ft_strncmp(cmd[i], "<<", 2))
		{
			if(!get_heredoc(p, cmd[i + 1], i))
				p->error = ft_strdup("nfile");
		}
		else if (!ft_strncmp(cmd[i], ">", 2))
		{
			if (!get_outfile(p, cmd[i + 1], i))
				p->error = ft_strdup("nfile");
		}
		else if (!ft_strncmp(cmd[i], ">>", 2))
		{
			if (!get_append(p, cmd[i + 1], i))
				p->error = ft_strdup("nfile");
		}
		i++;
	}
	if (p->error == NULL)
		p->error = ft_strdup("stop");
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
			// if (!chk_redirect_infile(&p->par.cmd[i],p->par.cmd[i].allcmd))
			// 	p->par.cmd[i].error = ft_strdup("nfile");
			// if (!chk_redirect_heredoc(&p->par.cmd[i], p->par.cmd[i].allcmd))
			// 	p->par.cmd[i].error = ft_strdup("heredoc");
			// if (!chk_redirect_outfile(&p->par.cmd[i], p->par.cmd[i].allcmd))
			// 	p->par.cmd[i].error = ft_strdup("nfile");
			// if (!chk_redirect_append(&p->par.cmd[i], p->par.cmd[i].allcmd))
			// 	p->par.cmd[i].error = ft_strdup("nfile");
		}
		i++;
	}
}

// void	print_chk_cmd2()

void	parser(t_pro *p)
{
	create_cmd_parser(p, p->lex.lst);
	print_chk_cmd(p);
	// chk_redirect(p);

	// 	add_redirect(p);
	// print_chk_cmd(p);

	// char	*ft_expand(char *ptr, t_pro *p)
}


//<in1<in2<in3<<eof>o1>o2>o3 | <in_1<in_2<in_3<<eof>o_1>o_2 |<<eof <<eof <<eof > o_2_1