/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:17:43 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/15 23:21:07 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
#include <sys/signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <dirent.h>
# include "color.h"
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <curses.h>

typedef struct s_lst
{
	int				token;
	char			*cmd;
	char			*content;
	struct s_lst	*next;
} 				t_lst;

typedef struct s_lexer
{
	char	*cmd;
	char	**split;
}				t_lex;

typedef struct s_program
{
	struct sigaction	id;
	t_lex				lex;
	t_lst				cmd;
}				t_pro;

// LEXER
void	lexer(t_pro *p);
char	**lexer_split(char *s, char *c);

// PARSER
void	parser(t_pro *p);

// EXPANDER

// EXECUTER
void	executer(t_pro *p);
// BUILDINFUNCTION
void	ft_echo(t_pro *p);
void	ft_pwd(t_pro *p);
void	ft_cd(t_pro *p);

#endif