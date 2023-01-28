/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:17:43 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/28 20:25:23 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/signal.h>
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

//typedef struct s_execute
//{
//	int			pipe_fd[2];
//	int			pid;
//}				t_exe;

typedef struct s_lexlst
{
	char			*content;
	struct s_lexlst	*next;
}				t_llst;

typedef struct s_infd
{
	int		pfd[2];
	int		pid;
	int		infd;
	int		outfd;
}				t_ifd;

typedef struct s_cmd
{
	int		index;
	int		cmdabpath;
	char	*cmd;
	char	**allcmd;
	char	*error;
	char	*heredoc;
	t_ifd	re;
} 				t_cmd;

typedef struct s_lexer
{
	int		status;
	// t_var	v;
	char	*cmd;
	char	*trim;
	t_llst	*lst;
}				t_lex;

typedef struct s_parser
{
	int		size;
	t_cmd	*cmd;
}				t_par;

typedef struct s_program
{
	char	*prompt;
	t_lex	lex;
	t_par	par;
	t_list	*ownenv;
}				t_pro;

// LEXER
void	lexer(t_pro *p);
char	*join_char(char *s, char c);

// PARSER
void	parser(t_pro *p);

// EXPANDER
void	expander(t_pro *p);
// char	*expander(char *s);
// EXECUTER
void	execute(t_pro *p, char **env);
// BUILDINFUNCTION
void	ft_echo(t_pro *p);
void	ft_pwd(t_pro *p);
void	ft_cd(t_pro *p);
char	*init_prompt(void);
void	ft_cpyenv(t_list **envlst, char **env);
t_list	*ft_findnodeenv(t_list **lstenv, char *env);
char	*ft_getenvval(char **ptrst, char **ptrend);

#endif