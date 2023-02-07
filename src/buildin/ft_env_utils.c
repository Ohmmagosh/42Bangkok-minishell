/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:27:43 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 01:28:10 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

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
			break ;
		tmplstenv = ft_lstnew(temenv);
		if (tmplstenv == NULL)
			break ;
		ft_lstadd_back(&lstenv, tmplstenv);
		envp++;
	}
	*envlst = lstenv;
}
