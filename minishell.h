/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:17:43 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 16:19:44 by psrikamo         ###   ########.fr       */
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

typedef struct s_lexlst
{
	char			*content;
	struct s_lexlst	*next;
}				t_llst;

typedef struct s_infd
{
	int		pfd[2];
	pid_t	pid;
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
}				t_cmd;

typedef struct s_lexer
{
	int		status;
	char	*stack;
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
int		lexer_lst_utils1(char *s, int i);
char	*subtrim(char *s);
char	*join_char(char *s, char c);
void	lexer(t_pro *p);
void	create_next(t_llst	*lst, char *s);
void	create_linklst(t_pro *p, char *s);
void	print_error(t_pro *p, char *s);
void	double_quote(t_pro *p, char *s, int *i);
void	single_quoate(t_pro *p, char *s, int *i);
void	plus_i(int *i, char c, char *s);
void	repipe(t_pro *p, int *i, char *s, int mode);
void	join_char_utils(t_pro *p, char *s, int *i);
void	redi(t_pro *p, int *i, char *s);
void	appendheredoc(t_pro *p, char *s, int *i);
void	lexer_init(t_pro *p, int *i);
void	lexer_lst_utils0(t_pro *p, int *i, char *s);
void	lexer_lst(t_pro *p, char *s);
t_llst	*create_head(char *s);

// PARSER
int		len_pipe(t_llst *p);
int		ismeta(char c);
int		here_doc_utils(char *name, char *eof);
int		len_cmd_allcmd(t_llst *lst);
int		ismetastr(char *s);
int		chk_redirect_cmd(char **cmd);
int		get_append(t_cmd *p, char *file, int ot);
int		get_infile(t_cmd *p, char *file, int ot);
int		get_outfile(t_cmd *p, char *file, int ot);
int		get_heredoc(t_cmd *p, char *eof, int i);
int		new_str_len(char **str);
char	*file_name_here_doc(int idx, int cmd);
char	*newrealloc(char *s);
char	**get_allcmd(t_llst *lst, int size);
char	**new_str_utils(char **str);
char	**new_str(char **cmd);
void	parser(t_pro *p);
void	print_lst(t_llst *p);
void	get_redirect_fd(t_cmd *p, char **cmd);
void	create_cmd_parser(t_pro *p, t_llst *lst);
void	free_split(char **bye);
void	get_redirect_fd_utils0(t_cmd *p, int *i);
void	get_redirect_fd_utils1(t_cmd *p, int *i, char **cmd);
t_cmd	init_cmd_parser(t_llst *p, int idx);
t_llst	*next_cmd(t_llst *lst);

// EXPANDER
char	*ft_expand(char *ptr, t_pro *p, int cmdabpath);
void	expander(t_pro *p);
void	new_expand(t_cmd *cmd, t_pro *p);

char	*ft_cratetestpath(char *path, char *cmd);
int		ft_chkbuldncmd(char *t_cmd);
char	*ft_searchabpath(char **t_spitpath, char *t_cmd);
void	ft_getabpath(char **cmd, t_pro *p);

void	ft_singlequote(char **t_ptrend, char **t_ptrst, char **t_res);
void	ft_dollarsign(char **t_ptrend, char **t_ptrst, char **t_res, t_pro *p);
void	ft_doublequote(char **t_ptrend, char **t_ptrst, char **t_res, t_pro *p);
char	*ft_clenptr(char *ptr, t_pro *p);

char	ft_chk_perm(char *path);
char	*ft_strcreate(char *st, char *end);
char	*ft_getenvval(char **ptrst, char **ptrend, t_pro *p);
void	ft_joinres(char **t_res, char **t_str);
char	*ft_getres(char *t_ptrst, char *t_ptrend, char **t_res);

// EXECUTER
void	ft_childrun(t_cmd *p, int lencmd, int i, t_list **ownenv);
void	ft_parentrun(t_cmd *p, int i, t_list **ownenv);
void	ft_exitstatus(t_cmd *p, int lencmd, int *t_status);
void	executer(t_cmd *p, char **env, int lencmd, t_list **ownenv);
void	execute(t_pro *p, char **env);

void	ft_openpipe(t_cmd *p, int lencmd);
void	ft_duprdwr(int *tmp_rd, int *tmp_wr);
void	ft_close0(t_cmd *p, int lencmd, int i);
void	ft_close1(t_cmd *p, int lencmd, int i);
void	ft_closeunlink(t_cmd *p, int i);

int		ft_chkbuldnconparent(char *cmd);
void	ft_budn_parent(t_cmd *p, int i, t_list **ownenv);
int		ft_chkbuldnconchild(char *cmd);
void	ft_budn_child(t_cmd *p, int i, t_list **ownenv);

// BUILDINFUNCTION
//  ECHO
void	ft_echonoopt(char **allcmd);
void	ft_echowtopt(char **allcmd);
//  PWD
void	ft_pwd(t_list **ownenv);
//  CD
void	ft_cd(t_list **ownenv, char *t_path);
char	*ft_chgtilde(char *t_path, t_list **ownenv);
void	ft_crate_oldpwd(t_list **ownenv, char **path);
void	ft_create_pwd(t_list **ownenv);
void	ft_cderr(char **path);
char	*ft_gethome(t_list **ownenv);
//  ENV
t_list	*ft_findnodeenv(t_list **lstenv, char *env);
char	*ft_createstatus(void);
char	*ft_getenv(t_list **lstenv, char *envvar);
void	ft_cutenvval(char **val);
void	ft_env(t_list **lstenv);

void	ft_cpyenv(t_list **envlst, char **envp);
//  EXPORT
void	ft_export(t_list **lstenv, char *arg);
char	*ft_createnameenv(char *arg);
void	ft_exportnull(t_list **lstenv);
//  UNSET
void	ft_unset(t_list **lstenv, char *arg);
//  EXIT
void	free_lex(t_pro *p);
void	free_par_help(t_pro *p, int i);
void	free_par(t_pro *p);
void	ft_exit(t_pro *p);

void	ft_lstclr(t_list **lst);
void	ft_freesplit(char ***split);

char	*init_prompt(void);
void	print_chk_cmd(t_pro *p);
#endif
