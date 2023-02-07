/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 21:59:55 by psrikamo          #+#    #+#             */
/*   Updated: 2023/02/08 01:03:44 by psrikamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

char	*ft_chgtilde(char *t_path, t_list **ownenv)
{
	char	*tmppath;

	if ((t_path == NULL) || (t_path[0] == '~'))
	{
		tmppath = ft_gethome(ownenv);
		if (t_path[0] == '~')
		{
			t_path = t_path + 1;
			while (*t_path != '\0')
			{
				tmppath = join_char(tmppath, *t_path);
				t_path++;
			}
		}
		return (tmppath);
	}
	else
		return (ft_strdup(t_path));
}

void	ft_crate_oldpwd(t_list **ownenv, char **path)
{
	char	*t_chr0;
	char	*t_chr1;
	char	*t_chr2;

	t_chr1 = *path;
	ft_unset(ownenv, "$OLDPWD");
	t_chr0 = ft_strdup("OLDPWD=");
	t_chr2 = ft_strjoin(t_chr0, t_chr1);
	free(t_chr0);
	free(t_chr1);
	*path = NULL;
	ft_export(ownenv, t_chr2);
	free(t_chr2);
}

void	ft_create_pwd(t_list **ownenv)
{
	char	*t_chr0;
	char	*t_chr1;
	char	*t_chr2;

	ft_unset(ownenv, "$PWD");
	t_chr0 = ft_strdup("PWD=");
	t_chr1 = getcwd(NULL, 0);
	t_chr2 = ft_strjoin(t_chr0, t_chr1);
	free(t_chr0);
	free(t_chr1);
	ft_export(ownenv, t_chr2);
	free(t_chr2);
}

void	ft_cderr(char **path)
{
	char	*t_chr;

	t_chr = *path;
	free(t_chr);
	write(1, "Cannot change directory\n", 24);
	g_status = 1;
}

void	ft_cd(t_list **ownenv, char *t_path)
{
	char	*path;
	char	*t_chr;

	path = ft_chgtilde(t_path, ownenv);
	if (((ft_chk_perm(path)) & (0b1000)) == 0)
	{
		write(1, "minihell No Such File or Directory\n", 35);
		g_status = 1;
		return ;
	}
	else
	{
		t_chr = getcwd(NULL, 0);
		if (chdir(path) != -1)
		{
			ft_crate_oldpwd(ownenv, &t_chr);
			ft_create_pwd(ownenv);
		}
		else
			ft_cderr(&t_chr);
	}
	free(path);
}

// void	ft_cd(t_list **ownenv, char *t_path)
// {
// 	char	*path;
// 	// char	*t_chr0;
// 	char	*t_chr1;
// 	// char	*t_chr2;
// 	char	perm;

// 	// printf("raw path:%s\n", t_path);
// 	path = ft_chgtilde(t_path, ownenv);
// 	// printf("cd for path:%s\n", path);
// 	perm = ft_chk_perm(path);
// 	if ((perm & (0b1000)) == 0)
// 	{
// 		// write(1, "No Such File or Directory\n", 26);
// 		write(1, "hell No Such File or Directory\n", 31);
// 		exit (1);
// 	}
// 	else
// 	{
// 		t_chr1 = getcwd(NULL, 0);
// 		if (chdir(path) != -1)
// 		{
// 			// ft_unset(ownenv, "$OLDPWD");
// 			// t_chr0 = ft_strdup("OLDPWD=");
// 			// t_chr2 = ft_strjoin(t_chr0, t_chr1);
// 			// free(t_chr0);
// 			// free(t_chr1);
// 			// ft_export(ownenv, t_chr2);
// 			// free(t_chr2);
// 			ft_crate_oldPWD(ownenv, &t_chr1);

// 			// ft_unset(ownenv, "$PWD");
// 			// t_chr0 = ft_strdup("PWD=");
// 			// t_chr1 = getcwd(NULL, 0);
// 			// t_chr2 = ft_strjoin(t_chr0, t_chr1);
// 			// free(t_chr0);
// 			// free(t_chr1);
// 			// ft_export(ownenv, t_chr2);
// 			// free(t_chr2);
// 			ft_create_PWD(ownenv);
// 		}
// 		else
// 		{
// 			free(t_chr1);
// 			write(1, "Cannot change directory\n", 24);
// 		}
// 	}
// 	free(path);
// }
