/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:26:27 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/06 15:54:29 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cpyenv(t_list **envlst, char **envp)
{
	char	*temenv;
	t_list	*tmplstenv;
	t_list	*lstenv;

	lstenv = NULL;
	while (*envp != NULL)
	{
		temenv = ft_strdup(*envp);
		if (temenv == NULL)
		{
			printf("cannot cpy %s\n", *envp);
			fflush(stdout);
			break;
		}
		tmplstenv = ft_lstnew(temenv);
		if (tmplstenv == NULL)
		{
			printf("cannot create node\n");
			fflush(stdout);
			break;
		}
		ft_lstadd_back(&lstenv,tmplstenv);
		envp++;
	}
	*envlst = lstenv;
}

// chk for $(name)
// env need to be in form $(env_name)
// env could be (env_name) => (optional)
// return "node" if env exist
// return "NULL" if env don't exist
t_list	*ft_findnodeenv(t_list **lstenv, char *env)
{
	char	*envname;
	char	*tmpenv;
	t_list	*tlstenv;

	// printf("search env:%s\n", env);
	tlstenv = *lstenv;
	while (tlstenv != NULL)
	{
		// envname = &env[1];
		if (env[0] == '$')
			envname = &env[1];
		else
			envname = &env[0];
		tmpenv = (char *)tlstenv->content;
		while (*envname != '\0')
		{
			if (*envname != *tmpenv)
				break;
			envname++;
			tmpenv++;
		}
		if ((*envname == '\0') && (*tmpenv == '='))
			return (tlstenv);
		tlstenv = tlstenv->next;
	}
	return (NULL);
}

char	*ft_createStatus(void)
{
	char	*env;
	char	*tmp_chr;
	
	env = ft_strdup("?=");
	tmp_chr = ft_itoa(g_status);
	while (*tmp_chr != '\0')
	{
		env = join_char(env, *tmp_chr);
		tmp_chr++;
	}
	// dprintf(2, "getenv ret:%s\n", env);
	return (env);
}

// chk for $(name)
// env need to be in form $(env_name)
// return value of env if env exist
// return "NULL" if env don't exist
char	*ft_getenv(t_list **lstenv, char *envvar)
{
	char	*env;
	size_t	siz;
	t_list	*noderes;

	// dprintf(2, "fn getenv envvar:%s\n", envvar);
	if (ft_strncmp(envvar, "$?", ft_strlen(envvar)) == 0)
	{
		env = ft_createStatus();
		return (env);
	}
	noderes = ft_findnodeenv(lstenv, envvar);
	if(noderes != NULL)
	{
		siz = ft_strlen((char *)noderes->content);
		env = malloc(sizeof(char) * (siz + 1));
		if (env != NULL)
		{
			env = ft_strdup((char *)noderes->content);
			return (env);
		}
		else
			return (env);
	}
	else
		return (NULL);
}

// input val ex PATH=/usr:/usr/bin
// output will be /usr:/usr/bin return in the same pointer
void	ft_cutenvval(char **val)
{
	size_t	len;
	char	*t_val0;
	char	*t_res;
	char	*res;

	t_val0 = *val;
	len = ft_strlen(t_val0);
	while (*t_val0 != '=')
		t_val0++;
	t_val0 = t_val0 + 1;
	t_res = malloc(sizeof(char) * len);
	res = t_res;
	while (*t_val0 != '\0')
	{
		*t_res = *t_val0;
		t_val0++;
		t_res++;
	}
	*t_res = '\0';
	t_val0 = *val;
	free(t_val0);
	*val = res;
}

void	ft_env(t_list **lstenv)
{
	t_list	*env;

	env = *lstenv;
	while (env != NULL)
	{
		// printf("%s\n", (char *)(env->content));
		// fflush(stdout);
		ft_putstr_fd((char *)(env->content), 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}
