/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:34:37 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 01:20:42 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

// arg must be (envname)
void	ft_unset(t_list **lstenv, char *arg)
{
	t_list	*tlstenv;
	t_list	*unsetenv;

	tlstenv = *lstenv;
	if (tlstenv != NULL)
	{
		unsetenv = ft_findnodeenv(lstenv, arg);
		if (unsetenv != NULL)
		{
			if (unsetenv == tlstenv)
			{
				*lstenv = unsetenv->next;
				free(unsetenv->content);
				free(unsetenv);
			}
			else
			{
				while (tlstenv->next != unsetenv)
					tlstenv = tlstenv->next;
				tlstenv->next = tlstenv->next->next;
				free(unsetenv->content);
				free(unsetenv);
			}
		}
	}
}
