/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:13:53 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 13:16:13 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_cratetestpath(char *path, char *cmd)
{
	char	*t_path;
	char	*t_cmd;

	t_path = ft_strdup(path);
	t_path = join_char(t_path, '/');
	t_cmd = cmd;
	while (*t_cmd != '\0')
	{
		t_path = join_char(t_path, *t_cmd);
		t_cmd++;
	}
	t_path = join_char(t_path, *t_cmd);
	return (t_path);
}

int	ft_chkbuldncmd(char *t_cmd)
{
	if ((ft_strncmp(t_cmd, "echo", ft_strlen(t_cmd)) != 0) && \
		(ft_strncmp(t_cmd, "cd", ft_strlen(t_cmd)) != 0) && \
		(ft_strncmp(t_cmd, "pwd", ft_strlen(t_cmd)) != 0) && \
		(ft_strncmp(t_cmd, "export", ft_strlen(t_cmd)) != 0) && \
		(ft_strncmp(t_cmd, "unset", ft_strlen(t_cmd)) != 0) && \
		(ft_strncmp(t_cmd, "env", ft_strlen(t_cmd)) != 0) && \
		(ft_strncmp(t_cmd, "exit", ft_strlen(t_cmd)) != 0))
		return (1);
	else
		return (0);
}

char	*ft_searchabpath(char **t_spitpath, char *t_cmd)
{
	char	*t_chr;

	t_chr = NULL;
	while (*t_spitpath != NULL)
	{
		t_chr = ft_cratetestpath(*t_spitpath, t_cmd);
		if ((ft_chk_perm(t_chr) & (0b0001)) != 0)
			break ;
		else
		{
			free(t_chr);
			t_chr = NULL;
		}
		t_spitpath++;
	}
	return (t_chr);
}

void	ft_getabpath(char **cmd, t_pro *p)
{
	char	*t_cmd;
	char	*t_path;
	char	**spitpath;
	char	*t_chr;

	t_cmd = *cmd;
	if (ft_chkbuldncmd(t_cmd))
	{
		t_path = ft_getenv(&p->ownenv, "$PATH");
		ft_cutenvval(&t_path);
		spitpath = ft_split(t_path, ':');
		if (t_path != NULL)
			free(t_path);
		t_chr = ft_searchabpath(spitpath, t_cmd);
		*cmd = t_chr;
		ft_freesplit(&spitpath);
		free(t_cmd);
	}
}
