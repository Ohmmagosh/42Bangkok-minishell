/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:10:05 by psuanpro          #+#    #+#             */
/*   Updated: 2022/03/24 23:10:04 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(&s[start]);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (len-- > 0 && ft_strlen(s) > start)
	{
		str[i++] = s[start++];
	}
	str[i] = '\0';
	return (str);
}
