/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:37:07 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 13:12:22 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>

extern int	g_status;

void	ft_lstclr(t_list **lst)
{
	t_list	*tmplst0;
	t_list	*tmplst1;

	tmplst0 = *lst;
	while (tmplst0 != NULL)
	{
		free(tmplst0->content);
		tmplst1 = tmplst0->next;
		free(tmplst0);
		tmplst0 = tmplst1;
	}
	*lst = NULL;
}

void	ft_freesplit(char ***split)
{
	char	**t_split;

	t_split = *split;
	while (*t_split != NULL)
	{
		free((*t_split));
		t_split++;
	}
	t_split = *split;
	free(t_split);
	*split = NULL;
}
