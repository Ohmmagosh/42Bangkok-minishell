/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:27:15 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/07 16:49:50 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

void	ft_pwd(t_list **ownenv)
{
	char	*t_pwd;

	t_pwd = getcwd(NULL, 0);
	ft_putstr_fd(t_pwd, 1);
	ft_putstr_fd("\n", 1);
	free(t_pwd);
}
