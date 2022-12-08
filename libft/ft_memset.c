/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 23:22:48 by psuanpro          #+#    #+#             */
/*   Updated: 2022/02/25 23:36:00 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;
	unsigned int	a;
	size_t			i;

	temp = b;
	a = c;
	i = 0;
	while (i < len)
	{
		temp[i] = a;
		i++;
	}
	return (temp);
}
