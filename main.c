/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:17:41 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/06 23:10:13 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handle(int signo, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;

	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_hand_main(void)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = SA_RESTART;
	sigemptyset(&sig_quit.sa_mask);
	sigaction(SIGQUIT, &sig_quit, NULL);
	sig_int.sa_sigaction = sig_handle;
	sig_int.sa_flags = SA_SIGINFO;
	sigemptyset(&sig_int.sa_mask);
	sigaction(SIGINT, &sig_int, NULL);
}

void	initmain(int ac, char **av)
{
	(void)ac;
	(void)av;
}

int	main(int argc, char **argv, char **env)
{
	t_pro	p;

	initmain(argc, argv);
	ft_cpyenv(&(p.ownenv), env);
	sig_hand_main();
	while (1)
	{
		p.lex.cmd = readline("\e[0;102mminishell->>\033[0m");
		if (p.lex.cmd != NULL)
		{
			if (*p.lex.cmd != '\0')
			{
				add_history(p.lex.cmd);
				if (ft_strncmp(p.lex.cmd, "exit\0", 6) == 0)
				{
					ft_putendl_fd("exit", 1);
					free(p.lex.cmd);
					exit(0);
				}
				lexer(&p);
				if (p.lex.status)
				{
					parser(&p);
					expander(&p);
					execute(&p, env);
				}
			}
			else
				free(p.lex.cmd);
		}
		else
		{
			write(1, "Found Ctrl+D => exit\n", 21);
			exit(0);
		}
	}
	return 0;
}
