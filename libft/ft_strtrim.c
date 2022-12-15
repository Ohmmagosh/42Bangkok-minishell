/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:43:17 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/13 20:14:15 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (ft_strchr(set, *(s1 + i)) && i < len)
		i++;
	while (ft_strchr(set, *(s1 + len - j)) && j < len)
		j++;
	if (i == len)
		return (ft_calloc(1, 1));
	return (ft_substr(s1, i, len - i - j + 1));
}
