/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:34:37 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/05 00:42:42 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// arg must be (envname)
void	ft_unset(t_list **lstenv, char *arg)
{
	t_list	*tlstenv;
	t_list	*unsetenv;

	// printf("arg:%s\n", arg);
	tlstenv = *lstenv;
	if (tlstenv != NULL)
	{
		unsetenv = ft_findnodeenv(lstenv, arg);
		// printf("content node:%s\n", (char *)unsetenv->content);
		if (unsetenv != NULL)
		{
			if (unsetenv == tlstenv)
			{
				*lstenv = unsetenv->next;
				free(unsetenv->content);
				// unsetenv->next = NULL;
				free(unsetenv);
			}
			else
			{
				while (tlstenv->next != unsetenv)
					tlstenv = tlstenv->next;
				// printf("contest pre:%s\n", (char *)tlstenv->content);
				// printf("contest node unset:%s\n", (char *)tlstenv->next->content);
				tlstenv->next = tlstenv->next->next;
				// printf("address %p\n", tlstenv->next);
				// printf("content in unset:%s\n", (char *)unsetenv->content);
				// fflush(stdout);
				free(unsetenv->content);
				// unsetenv->next = NULL;
				free(unsetenv);
			}
		}
	}
}