/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:27:37 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/13 20:11:55 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	int					opt;
	unsigned long long	number;

	number = 0;
	opt = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			opt *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += *str - 48;
		if (number > 9223372036854775807 && opt > 0)
			return (-1);
		if (number > 9223372036854775807 && opt < 0)
			return (0);
		str++;
	}
	return (opt * number);
}
