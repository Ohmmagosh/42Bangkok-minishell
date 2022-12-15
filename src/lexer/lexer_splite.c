/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_splite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:19:23 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/15 23:22:38 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_deli_mini(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_word_mini(char *s, char *c)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (s[i])
	{

		i++;
	}
	return (ret);
}

char	**lexer_split(char *s, char *c)
{
	char	**ret;
	int		i;

	i = 0;
	if (!s || !c)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * count_word_mini(s, c));
	if (!ret)
		return (NULL);
	return (ret);
}