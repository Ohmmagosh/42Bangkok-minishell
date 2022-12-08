/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_untils_c.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:48:58 by psuanpro          #+#    #+#             */
/*   Updated: 2022/05/23 03:17:15 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	len;

	len = 0;
	if (s == NULL)
	{
		return (write(1, "(null)", 6));
	}
	while (s[len] != '\0')
	{
		write(1, &s[len], 1);
		len++;
	}
	return (len);
}

int	ft_ox(void)
{
	write(1, "0x", 2);
	return (2);
}
