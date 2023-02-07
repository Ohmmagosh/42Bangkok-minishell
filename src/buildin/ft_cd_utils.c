/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:00:52 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 01:21:44 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

char	*ft_gethome(t_list **ownenv)
{
	char	*homenv;

	homenv = ft_getenv(ownenv, "$HOME");
	if (homenv == NULL)
	{
		printf("$HOME not exist\n");
		g_status = 1;
		return (NULL);
	}
	else
	{
		ft_cutenvval(&homenv);
	}
	return (homenv);
}
