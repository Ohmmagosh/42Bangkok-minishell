/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:28:13 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/05 00:11:52 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void    ft_pwd(t_list **ownenv)
{
    char    *t_pwd;

    // t_pwd = ft_getenv(ownenv, "$PWD");
    // printf("get env pwd:%s\n", t_pwd);
    // ft_cutenvval(&t_pwd);
    t_pwd = getcwd(NULL, 0);
    // printf("res cmd:%s\n", t_pwd);
    // fflush(stdout);
    ft_putstr_fd(t_pwd, 1);
    ft_putstr_fd("\n", 1);
    free(t_pwd);
}