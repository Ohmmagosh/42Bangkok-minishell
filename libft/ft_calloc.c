/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:56:14 by psuanpro          #+#    #+#             */
/*   Updated: 2022/03/25 19:07:30 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	byte;
	void	*str;

	byte = count * size;
	str = (char *)malloc(byte);
	if (!str)
		return (NULL);
	ft_bzero(str, byte);
	return (str);
}
