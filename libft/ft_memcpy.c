/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:37:43 by psuanpro          #+#    #+#             */
/*   Updated: 2022/03/24 23:46:53 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s1;
	char	*d1;
	size_t	i;

	s1 = (char *)src;
	d1 = (char *)dst;
	i = 0;
	if (!s1 && !d1)
		return (dst);
	while (i < n)
	{
		d1[i] = s1[i];
		i++;
	}
	return (dst);
}
