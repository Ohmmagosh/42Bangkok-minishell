/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:26:27 by psrikamo          #+#    #+#             */
/*   Updated: 2023/01/22 23:26:30 by psrikamo         ###   ########.fr       */
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