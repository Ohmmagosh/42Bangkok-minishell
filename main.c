/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:17:41 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/01 16:37:27 by psuanpro         ###   ########.fr       */
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

// int	main(void)
int	main(int argc, char **argv, char **env)
{
	t_pro	p;

	(void)argc;
	(void)argv;
	// struct sigaction	sig_quit;
	// struct sigaction	sig_int;

	// sig_quit.sa_sigaction = sig_handle;
	// sig_quit.sa_handler = SIG_IGN;
	// sigaction(SIGQUIT, &sig_quit, NULL);
	// sig_int.sa_sigaction = sig_handle;
	// sig_int.sa_flags = SA_SIGINFO;
	// sigaction(SIGINT, &sig_int, NULL);

	// ft_cpyenv(&ownenv, envp);
	ft_cpyenv(&(p.ownenv), env);

	// printf("show cpy env\n");
	// t_list	*tmpenv = p.ownenv;
	// while (tmpenv != NULL)
	// {
	// 	printf("env:%s\n", (char *)tmpenv->content);
	// 	tmpenv = tmpenv->next;
	// }
	// printf("end show cpy env\n");

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
			//expander(&p);
			//execute(&p, env);
			//dprintf(2,"%s----------hello----------%s\n", "\e[42m", "\e[0m");
		}
	}
	return 0;
}
