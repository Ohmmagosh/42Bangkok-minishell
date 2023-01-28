/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:26:27 by psrikamo          #+#    #+#             */
/*   Updated: 2023/01/29 02:44:27 by psrikamo         ###   ########.fr       */
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
			break;
		}
		tmplstenv = ft_lstnew(temenv);
		if (tmplstenv == NULL)
		{
			printf("cannot create node\n");
			break;
		}
		ft_lstadd_back(&lstenv,tmplstenv);
		envp++;
	}
	*envlst = lstenv;
}

// chk for $(name)
// env need to be in form $(env_name)
// return "node" if env exist
// return "NULL" if env don't exist
t_list	*ft_findnodeenv(t_list **lstenv, char *env)
{
	char	*envname;
	char	*tmpenv;
	t_list	*tlstenv;

	printf("search env:%s\n", env);
	tlstenv = *lstenv;
	while (tlstenv != NULL)
	{
		envname = &env[1];
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

// chk for $(name)
// env need to be in form $(env_name)
// return value of env if env exist
// return "NULL" if env don't exist
char	*ft_getenv(t_list **lstenv, char *envvar)
{
	char	*env;
	size_t	siz;
	t_list	*noderes;

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
