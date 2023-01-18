/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:17:41 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/16 21:59:55 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	sig_handle(int signo, siginfo_t *info, void *ucontext)
// {
// 	(void)ucontext;
// 	(void)info;

// 	if (signo == SIGQUIT)
// 	{
// 		// printf("found ctrl+\\\n");
// 		// rl_redisplay();
// 		// rl_on_new_line();
// 		// rl_replace_line("minihell>", 9);
// 	}
// 	else if (signo == SIGINT)
// 	{
// 		// printf("found Ctrl+C\n");
// 		rl_redisplay();
// 		rl_replace_line("", 0);
// 		rl_replace_line("minihell>", 9);
// 		// rl_on_new_line();
// 	}
// }

int	main(void)
{
	t_pro	p;
	// struct sigaction	sig_quit;
	// struct sigaction	sig_int;

	// sig_quit.sa_sigaction = sig_handle;
	// sig_quit.sa_handler = SIG_IGN;
	// sigaction(SIGQUIT, &sig_quit, NULL);
	// sig_int.sa_sigaction = sig_handle;
	// sig_int.sa_flags = SA_SIGINFO;
	// sigaction(SIGINT, &sig_int, NULL);
	while (1)
	{
		// p.prompt = init_prompt();
		p.lex.cmd = readline("\e[0;102mminishell->>\033[0m");
		// if (p.lex.cmd == NULL)
		// {
		// 	printf("found Ctrl+D\n");
		// 	exit(0);
		// }
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
		}
	}
	return 0;
}
