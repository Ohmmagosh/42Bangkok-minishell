/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 03:36:38 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/07 20:35:42 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_len_nl_gnl(char *s)
{
	int	i;

	i = 0;
	while (s != NULL && *(s + i) != '\0')
	{	
		if (*(s + i) == '\n')
		{	
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str1;
	size_t	i;
	size_t	j;

	j = ft_strlen_gnl(s1);
	i = (ft_strlen_gnl(s1) + ft_strlen_gnl(s2));
	str1 = (char *)malloc(sizeof(char) * (i + 1));
	if (!str1)
		return (NULL);
	while (s1 && *s1)
		*str1++ = *s1++;
	while (s2 && *s2)
		*str1++ = *s2++;
	*str1 = '\0';
	str1 = str1 - i;
	if (s1)
		free(s1 - j);
	return (str1);
}

int	ft_chk_stash_gnl(char *s)
{
	int	i;

	i = 0;
	while (s != NULL && *(s + i))
	{	
		if (*(s + i) == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strcpy_gnl(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc((sizeof(char) * ft_len_nl_gnl(s)) + 1);
	if (!ret)
		return (NULL);
	while (ft_len_nl_gnl(s) - i)
	{
		*(ret + i) = *(s + i);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_clear_stash_gnl(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc((sizeof(char) * (ft_strlen_gnl(s) - ft_len_nl_gnl(s))) + 1);
	if (!ret)
		return (NULL);
	while (s && *(s + i) != '\0' && i < ft_strlen_gnl(s) - ft_len_nl_gnl(s))
	{
		*(ret + i) = *(s + ft_len_nl_gnl(s) + i);
		i++;
	}
	if (s)
		free(s);
	*(ret + i) = '\0';
	if (ret[0] == '\0')
	{	
		free(ret);
		return (NULL);
	}
	return (ret);
}
