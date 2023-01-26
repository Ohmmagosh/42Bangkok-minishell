/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:46:22 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/26 20:32:37 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <unistd.h>


typedef struct s_test
{
	int		idx;
	int		pfd[2];
	int		pid;
	char	**cmd;
} 				t_test;

// void	test_executer(void)
// {
// 	//if 5 cmd will create 4 pipe
// 	//ls -la | wc -l
// 	int	i = 0;
// 	// while (i < 2)
// 	// {
// 	// 	pipe();
// 	// }
// }

void	close_pipe(t_test *p, int idx, int lencmd)
{
	int	i;

	i= 0;
	if (lencmd == 1)
		return;
	while (i < lencmd)
	{
		// if (idx == 0)
		// 	close(p[i].pfd[0]);
		if (i == idx - 1)
			close(p[i].pfd[1]);
		if (i != idx && i == idx - 1)
		{
			close(p[i].pfd[0]);
			close(p[i].pfd[1]);
		}
		i++;
		// dprintf(0, "ja ekk 0 i --> %d\n", i);
	}
}

void	test_cmd(t_test *p, char **env, int	lencmd)
{
	int	i;
	int	tmp_rd;
	int	tmp_wr;
	
	i = 0;
	while (i < lencmd)
	{
		if (i != lencmd - 1)
			pipe(p[i].pfd);
		i++;
	}
	i = 0;
	tmp_rd = dup(0);
	tmp_wr = dup(1);
	while (i < lencmd)
	{
				// dprintf(2, "hello100 ---> %d\n", i);
		p[i].pid = fork();
		if (p[i].pid == 0)
		{
			if (i == 0 && lencmd != 1)
			{
				dup2(p[i].pfd[1], 1);
			}
			else if (i == lencmd - 1 && lencmd != 1)
			{
				dup2(p[i - 1].pfd[0], 0);
			}
			else if (lencmd != 1)
			{
				dup2(p[i - 1].pfd[0], 0);
				dup2(p[i].pfd[1], 1);
			}
			// if (lencmd != 1)
			
			close_pipe(p , i, lencmd);
				// dprintf(2, "hello\n");
			// dprintf(1, "i %d\n", i);
			execve(p[i].cmd[0], p[i].cmd, env);
		}
		else
		{
			if (i != 0)
			{
				dup2(tmp_rd, 0);
				dup2(tmp_wr, 1);
				close(p[i - 1].pfd[0]);
				close(p[i - 1].pfd[1]);
			}
		}
		i++;
	}
	i = 0;
	int	status;
	while (i < lencmd)
	{
		waitpid(p[i].pid, &status, 0);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_test	*allcmd;
	(void)ac;
	(void)av;
	int	cmds = 1;
	allcmd = (t_test *)malloc(sizeof(t_test) * cmds);
	allcmd[0].cmd = ft_split("/bin/cat", ' ');
	allcmd[0].idx = 0;

	allcmd[1].cmd = ft_split("/bin/cat", ' ');
	allcmd[1].idx = 1;

	allcmd[2].cmd = ft_split("/bin/ls", ' ');
	allcmd[2].idx = 2;

	// allcmd[3].cmd = ft_split("/usr/bin/sort", ' ');
	// allcmd[3].idx = 3;

	// allcmd[0].cmd = ft_split("/bin/echo hello", ' ');
	// allcmd[0].idx = 0;

	// allcmd[1].cmd = ft_split("/usr/bin/rev", ' ');
	// allcmd[1].idx = 1;


	test_cmd(allcmd, env, cmds);
	
}