/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:41:24 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/13 20:12:46 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	lenght;

	lenght = ft_strlen(dst);
	dst += lenght;
	if (lenght > dstsize)
		return (dstsize + ft_strlen(src));
	while (lenght < dstsize - 1 && *src && dstsize != 0)
	{
		*dst = *src;
		dst++;
		src++;
		lenght++;
	}
	*dst = '\0';
	return (lenght + ft_strlen(src));
}
