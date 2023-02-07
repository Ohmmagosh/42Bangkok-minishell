/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:26:27 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 01:28:12 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

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

	tlstenv = *lstenv;
	while (tlstenv != NULL)
	{
		if (env[0] == '$')
			envname = &env[1];
		else
			envname = &env[0];
		tmpenv = (char *)tlstenv->content;
		while (*envname != '\0')
		{
			if (*envname != *tmpenv)
				break ;
			envname++;
			tmpenv++;
		}
		if ((*envname == '\0') && (*tmpenv == '='))
			return (tlstenv);
		tlstenv = tlstenv->next;
	}
	return (NULL);
}

char	*ft_createstatus(void)
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

	if (ft_strncmp(envvar, "$?", ft_strlen(envvar)) == 0)
	{
		env = ft_createstatus();
		return (env);
	}
	noderes = ft_findnodeenv(lstenv, envvar);
	if (noderes != NULL)
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
		ft_putstr_fd((char *)(env->content), 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}
