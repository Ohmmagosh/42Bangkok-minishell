/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:34:25 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 13:09:04 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

void	ft_exportnull(t_list **lstenv)
{
	t_list	*tlstenv;

	tlstenv = *lstenv;
	while (tlstenv != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd((char *)(tlstenv->content), 1);
		ft_putstr_fd("\n", 1);
		tlstenv = tlstenv->next;
	}
}

char	*ft_createnameenv(char *arg)
{
	char	*envend;
	char	*envname;
	char	*envst;

	envend = arg;
	envname = NULL;
	while ((*envend != '=') && (*envend != '\0'))
		envend++;
	if (*envend == '=')
	{
		envname = malloc((envend - arg) + 1);
		envst = arg;
		while (envst != envend)
		{
			envname = join_char(envname, *envst);
			envst++;
		}
	}
	return (envname);
}

// arg need to "(envname)=(value)"
void	ft_export(t_list **lstenv, char *arg)
{
	t_list	*tlstenv;
	char	*envname;

	envname = ft_createnameenv(arg);
	if (envname != NULL)
	{
		tlstenv = ft_findnodeenv(lstenv, envname);
		if (tlstenv == NULL)
			ft_lstadd_back(lstenv, ft_lstnew(ft_strdup(arg)));
		else
		{
			free(tlstenv->content);
			tlstenv->content = ft_strdup(arg);
		}
		free(envname);
	}
}
