/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:46:22 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/31 00:12:18 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

//typedef struct s_test
//{
//	int		idx;
//	int		pfd[2];
//	int		pid;
//	char	**cmd;
//} 				t_test;

//// void	test_executer(void)
//// {
//// 	//if 5 cmd will create 4 pipe
//// 	//ls -la | wc -l
//// 	int	i = 0;
//// 	// while (i < 2)
//// 	// {
//// 	// 	pipe();
//// 	// }
//// }

void	close_pipe(t_cmd *p, int idx, int lencmd)
{
	int	i;

	i= 0;
	//dprintf(2,"%s----------close pipe----------%s\n", "\e[42m", "\e[0m");
	if (lencmd == 1)
		return;
	while (i < lencmd)
	{
		// if (idx == 0)
		// 	close(p[i].pfd[0]);
		if (i == idx - 1)
			close(p[i].re.pfd[1]);
		if (i != idx && i == idx - 1)
		{
			close(p[i].re.pfd[0]);
			close(p[i].re.pfd[1]);
		}
		i++;
		// dprintf(0, "ja ekk 0 i --> %d\n", i);
	}
}

void	executer(t_cmd *p, char **env, int lencmd, t_list **ownenv)
{
	int	i;
	int	tmp_rd;
	int	tmp_wr;

	int	retdup2;
	
	i = 0;
	while (i < lencmd)
	{
		//printf("%s----------hello----------%s\n", "\e[42m", "\e[0m");
		if (i != lencmd - 1)
		{
			pipe(p[i].re.pfd);
		}
		i++;
	}
	i = 0;
	tmp_rd = dup(0);
	tmp_wr = dup(1);
	while (i < lencmd)
	{
		p[i].re.pid = fork();
		//dprintf(2,"p[i].re.pid -> %d\n", p[i].re.pid);
		if (p[i].re.pid == 0)
		{
			if (i == 0 && lencmd != 1)
			{
				dprintf(2,"%s----------1----------%s\n", "\e[42m", "\e[0m");
				// dup2(p[i].re.pfd[1], 1);
				retdup2 = dup2(p[i].re.pfd[1], 1);
				// dprintf(2,"%s----------1----------%s  retdup2%d\n", "\e[42m", "\e[0m", retdup2);

			}
			else if (i == lencmd - 1 && lencmd != 1)
			{
				dprintf(2,"%s----------2----------%s\n", "\e[42m", "\e[0m");
				// dup2(p[i - 1].re.pfd[0], 0);
				retdup2 = dup2(p[i - 1].re.pfd[0], 0);
				// dprintf(2,"%s----------2----------%s  retdup2%d\n", "\e[42m", "\e[0m", retdup2);
			}
			else if (lencmd != 1)
			{
				dprintf(2,"%s----------3----------%s\n", "\e[42m", "\e[0m");
				// dup2(p[i - 1].re.pfd[0], 0);
				// dup2(p[i].re.pfd[1], 1);
				retdup2 = dup2(p[i - 1].re.pfd[0], 0);
				// dprintf(2,"%s----------3----------%s  retdup2%d\n", "\e[42m", "\e[0m", retdup2);
				retdup2 = dup2(p[i].re.pfd[1], 1);
				// dprintf(2,"%s----------3----------%s  retdup2%d\n", "\e[42m", "\e[0m", retdup2);
			}
			// close_pipe(p , i, lencmd);
			
			// execve(p[i].allcmd[0], p[i].allcmd, env);

			// if build in cmd
			// 	if echo pwd env
			// 		call function build in
			// 	else
			// 		exit ();

			close_pipe(p , i, lencmd);

			if ( (ft_strncmp(p[i].allcmd[0], "echo", ft_strlen(p[i].allcmd[0])) == 0) || \
				(ft_strncmp(p[i].allcmd[0], "cd", ft_strlen(p[i].allcmd[0])) == 0) || \
				(ft_strncmp(p[i].allcmd[0], "pwd", ft_strlen(p[i].allcmd[0])) == 0) || \
				(ft_strncmp(p[i].allcmd[0], "export", ft_strlen(p[i].allcmd[0])) == 0) || \
				(ft_strncmp(p[i].allcmd[0], "unset", ft_strlen(p[i].allcmd[0])) == 0) || \
				(ft_strncmp(p[i].allcmd[0], "env", ft_strlen(p[i].allcmd[0]))== 0) || \
				(ft_strncmp(p[i].allcmd[0], "exit", ft_strlen(p[i].allcmd[0])) == 0) )
			{
				if (ft_strncmp(p[i].allcmd[0], "pwd", ft_strlen(p[i].allcmd[0])) == 0)
				{
					ft_pwd(ownenv);
					exit(0);
				}
				else if (ft_strncmp(p[i].allcmd[0], "echo", ft_strlen(p[i].allcmd[0])) == 0)
				{
					if (ft_strncmp(p[i].allcmd[1], "-n", ft_strlen(p[i].allcmd[1])) == 0)
					{
						ft_echowtopt(p[i].allcmd);
						exit(0);
					}
					else
					{
						ft_echonoopt(p[i].allcmd);
						exit(0);
					}
				}
				else if (ft_strncmp(p[i].allcmd[0], "env", ft_strlen(p[i].allcmd[0]))== 0)
				{
					ft_env(ownenv);
					exit(0);
				}
				else
					exit (0);
			}

			dprintf(2, "%s----------Should not show----------%s\n", "\e[42m", "\e[0m");
			
			execve(p[i].allcmd[0], p[i].allcmd, env);

			// char	*a[] = {"/bin/ls", NULL};
			// execve("/bin/ls",a , env);

			//dprintf(2,"%s----------after exe----------%s\n", "\e[42m", "\e[0m");
			//printf("%s----------after exe----------%s\n", "\e[42m", "\e[0m");
			//exit(0);
			
		}
		else
		{
			dprintf(2,"%s----------TEST----------%s\n", "\e[42m", "\e[0m");

			if ( (ft_strncmp(p[i].allcmd[0], "echo", ft_strlen(p[i].allcmd[0])) == 0) || \
				(ft_strncmp(p[i].allcmd[0], "cd", ft_strlen(p[i].allcmd[0])) == 0) || \
				(ft_strncmp(p[i].allcmd[0], "pwd", ft_strlen(p[i].allcmd[0])) == 0) || \
				(ft_strncmp(p[i].allcmd[0], "export", ft_strlen(p[i].allcmd[0])) == 0) || \
				(ft_strncmp(p[i].allcmd[0], "unset", ft_strlen(p[i].allcmd[0])) == 0) || \
				(ft_strncmp(p[i].allcmd[0], "env", ft_strlen(p[i].allcmd[0]))== 0) || \
				(ft_strncmp(p[i].allcmd[0], "exit", ft_strlen(p[i].allcmd[0])) == 0) )
			{
				if (ft_strncmp(p[i].allcmd[0], "export", ft_strlen(p[i].allcmd[0])) == 0)
				{
					ft_export(ownenv, p[i].allcmd[1]);
					// exit(0);
				}
				else if (ft_strncmp(p[i].allcmd[0], "unset", ft_strlen(p[i].allcmd[0])) == 0)
				{
					ft_unset(ownenv, p[i].allcmd[1]);
					// exit(0);
				}
				else if (ft_strncmp(p[i].allcmd[0], "cd", ft_strlen(p[i].allcmd[0])) == 0)
				{
					ft_cd(ownenv, p[i].allcmd[1]);
					// exit(0);
				}
			}

			//waitpid(p[i].re.pid, 0, 0);
			if (i != 0)
			{
				// dprintf(2,"%s----------parent----------%s\n", "\e[42m", "\e[0m");
				// dup2(tmp_rd, 0);
				// dup2(tmp_wr, 1);
				// close(p[i - 1].re.pfd[0]);
				// close(p[i - 1].re.pfd[1]);

				dprintf(2,"%s----------parent----------%s\n", "\e[42m", "\e[0m");

				// if build in cmd
				// 	if cd export unset exit
				// 		call fn build in
				

				// dup2(tmp_rd, 0);
				// dup2(tmp_wr, 1);
				retdup2 = dup2(tmp_rd, 0);
				// dprintf(2,"%s----------parent----------%s 0%d\n", "\e[42m", "\e[0m", retdup2);
				retdup2 = dup2(tmp_wr, 1);
				// dprintf(2,"%s----------parent----------%s 0%d\n", "\e[42m", "\e[0m", retdup2);
				close(p[i - 1].re.pfd[0]);
				close(p[i - 1].re.pfd[1]);
			}
		}
		i++;
	}
	i = 0;
	int	status;
	//printf(" -> %d\n", );
	while (i < lencmd)
	{
		//printf("i -> %d\n", i);
		waitpid(p[i].re.pid, &status, 0);
		i++;
	}
	//dprintf(2,"%s----------hello child <<<<<<----------%s\n", "\e[42m", "\e[0m");
}

//int	main(int ac, char **av, char **env)
//{
//	t_test	*allcmd;
//	(void)ac;
//	(void)av;
//	int	cmds = 3;
//	allcmd = (t_test *)malloc(sizeof(t_test) * cmds);
//	allcmd[0].cmd = ft_split("/bin/cat", ' ');
//	allcmd[0].idx = 0;

//	allcmd[1].cmd = ft_split("/bin/cat", ' ');
//	allcmd[1].idx = 1;

//	allcmd[2].cmd = ft_split("/bin/ls", ' ');
//	allcmd[2].idx = 2;

//	// allcmd[3].cmd = ft_split("/usr/bin/sort", ' ');
//	// allcmd[3].idx = 3;

//	// allcmd[0].cmd = ft_split("/bin/echo hello", ' ');
//	// allcmd[0].idx = 0;

//	// allcmd[1].cmd = ft_split("/usr/bin/rev", ' ');
//	// allcmd[1].idx = 1;


	
//}
//	test_cmd(allcmd, env, cmds);
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
			printf("allcmd[%d] %s\n", j,p->par.cmd[i].allcmd[j]);
			j++;
		}
		i++;
	}
}

void	execute(t_pro *p, char **env)
{
	printf("%s----------execute----------%s\n", "\e[42m", "\e[0m");
	print_chk_cmd(p);
	executer(p->par.cmd, env, p->par.size, &(p->ownenv));
}