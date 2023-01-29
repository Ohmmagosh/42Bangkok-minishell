/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:28:13 by psrikamo          #+#    #+#             */
/*   Updated: 2023/01/29 19:54:46 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void    ft_pwd(t_list **ownenv)
{
    char    *t_pwd;

    t_pwd = ft_getenv(ownenv, "$PWD");
    printf("get env pwd:%s\n", t_pwd);
    ft_cutenvval(&t_pwd);
    printf("res cmd:%s\n", t_pwd);
    fflush(stdout);
    exit(0);
}