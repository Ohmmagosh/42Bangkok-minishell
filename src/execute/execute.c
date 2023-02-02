/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:46:22 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/02 23:01:26 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

//void	close_pipe(t_cmd *p, int idx, int lencmd)
//{
//	int	i;

//	i= 0;
//	//dprintf(2,"%s----------close pipe----------%s\n", "\e[42m", "\e[0m");
//	if (lencmd == 1)
//		return;
//	while (i < lencmd)
//	{
//		// if (idx == 0)
//		// 	close(p[i].pfd[0]);
//		if (i == idx - 1)
//			close(p[i].re.pfd[1]);
//		if (i != idx && i == idx - 1)
//		{
//			close(p[i].re.pfd[0]);
//			close(p[i].re.pfd[1]);
//		}
//		i++;
//		// dprintf(0, "ja ekk 0 i --> %d\n", i);
//	}
//}

void	executer(t_cmd *p, char **env, int lencmd, t_list **ownenv)
{
	int	i;
	int	tmp_rd;
	int	tmp_wr;

	i = 1;
	while (i < lencmd)
	{
		pipe(p[i].re.pfd);
		i++;
	}
	i = 0;
	tmp_rd = dup(0);
	tmp_wr = dup(1);
	while (i < lencmd)
	{
		p[i].re.pid = fork();
		if (p[i].re.pid == 0)
		{
			if (i != lencmd - 1)//not last commmand
			{
				for(int a = 1; a < lencmd; a++)
				{
					close(p[a].re.pfd[0]);
					if (a != i + 1)
						close(p[a].re.pfd[1]);
				}
				dup2(p[i + 1].re.pfd[1], STDOUT_FILENO);
			}
			if (i != 0)//not first command
			{
				for(int a = 1; a < lencmd; a++)
				{
					close(p[a].re.pfd[1]);
					if (a != i)
						close(p[a].re.pfd[0]);
				}
				dup2(p[i].re.pfd[0], STDIN_FILENO);
			}
			//dprintf(2, "hello 1 cmd\n");
			dup2(p[i].re.infd, STDIN_FILENO);
			dup2(p[i].re.outfd, STDOUT_FILENO);
			if ((ft_strncmp(p[i].allcmd[0], "echo", ft_strlen(p[i].allcmd[0])) == 0) || \
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
			execve(p[i].allcmd[0], p[i].allcmd, env);
		}
		else
		{
			if ((ft_strncmp(p[i].allcmd[0], "echo", ft_strlen(p[i].allcmd[0])) == 0) || \
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


				 dup2(tmp_rd, 0);
				 dup2(tmp_wr, 1);
				//dup2(tmp_rd, 0);

				//dprintf(0,"%s----------parent----------%s 0%d\n", "\e[42m", "\e[0m", dup2(tmp_rd, 0));
				////dup2(tmp_wr, 1);
				//dprintf(0,"%s----------parent----------%s 0%d\n", "\e[42m", "\e[0m", dup2(tmp_wr, 1));
				close(p[i].re.pfd[0]);
				close(p[i].re.pfd[1]);
			}
			dup2(STDIN_FILENO,tmp_rd);
			dup2(STDOUT_FILENO,tmp_wr);
		}
		i++;
	}
	while(wait(NULL) != -1);
	i = 0;
	int	status;
	while (i < lencmd)
	{
		//printf("i -> %d\n", i);
		waitpid(p[i].re.pid, &status, 0);
		i++;
	}
	//dprintf(2,"%s----------hello child <<<<<<----------%s\n", "\e[42m", "\e[0m");
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
			printf("allcmd[%d] %s\n", j,p->par.cmd[i].allcmd[j]);
			j++;
		}
		i++;
	}
}

void	execute(t_pro *p, char **env)
{
	//printf("%s----------execute----------%s\n", "\e[42m", "\e[0m");
	//print_chk_cmd(p);
	//exit(0);
	executer(p->par.cmd, env, p->par.size, &(p->ownenv));
}
