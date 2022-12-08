/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:57:44 by psuanpro          #+#    #+#             */
/*   Updated: 2022/03/21 22:35:30 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	unit(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*zero(void)
{
	char	*str;

	str = malloc(2);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*positive(int n)
{
	char	*str;
	int		i;

	str = malloc(unit(n) + 1);
	i = unit(n);
	str += i;
	*str = '\0';
	while (n > 0)
	{
		str--;
		*str = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*negative(int n)
{
	unsigned int		nbr;
	char				*str;
	int					i;

	str = malloc(unit(n) + 2);
	if (!str)
		return (NULL);
	nbr = n * -1;
	*str = '-';
	i = unit(n) + 1;
	str += i;
	*str = '\0';
	while (nbr > 0)
	{
		str--;
		*str = nbr % 10 + '0';
		nbr /= 10;
	}
	str--;
	return (str);
}

char	*ft_itoa(int n)
{
	if (n == 0)
		return (zero());
	if (n < 0)
		return (negative(n));
	return (positive(n));
}
