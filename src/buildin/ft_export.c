/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:34:25 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/05 00:14:14 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exportNull(t_list **lstenv)
{
	t_list	*tlstenv;

	tlstenv = *lstenv;
	while (tlstenv != NULL)
	{
		// printf("%s\n", (char *)(tlstenv->content));
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd((char *)(tlstenv->content), 1);
		ft_putstr_fd("\n", 1);
		tlstenv = tlstenv->next;
	}
}

// arg need to "(envname)=(value)"
void	ft_export(t_list **lstenv, char *arg)
{
	t_list	*tlstenv;
	char	*envend;
	char	*envst;
	char	*envname;
	char	*tmpenvname;

    printf("fn export\n");
	printf("arg:%s\n", arg);
	envend = arg;
	while (*envend != '=')
		envend++;
	envname = malloc((envend - arg) + 1);
    // envname[0] = '$';
	tmpenvname = envname;
	envst = arg;
	while (envst != envend)
	{
		*tmpenvname = *envst;
		tmpenvname++;
		envst++;
	}
	*tmpenvname = '\0';
	printf("arg cut:%s\n", envname);

	tlstenv = ft_findnodeenv(lstenv, envname);
	if (tlstenv == NULL)
		ft_lstadd_back(lstenv, ft_lstnew(ft_strdup(arg)));
	else
	{
		printf("show env:%s\n", (char *)tlstenv->content);
		fflush(stdout);
		free(tlstenv->content);
		tlstenv->content = ft_strdup(arg);
	}

	free(envname);
}