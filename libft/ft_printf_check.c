/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:24:35 by psuanpro          #+#    #+#             */
/*   Updated: 2022/05/23 03:08:21 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_check(const char *s, va_list ap)
{
	int	count;

	count = 0;
	if (*(s + 1) == 'd' )
		count += ft_putnbr(va_arg(ap, int));
	else if (*(s + 1) == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (*(s + 1) == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (*(s + 1) == '%')
		count += ft_putchar((int)*s);
	else if (*(s + 1) == 'p')
	{
		count += ft_ox();
		count += ft_putnbr_hex_p(va_arg(ap, size_t));
	}
	else if (*(s + 1) == 'x')
		count += ft_putnbr_hex(va_arg(ap, unsigned int));
	else if (*(s + 1) == 'i')
		count += ft_putnbr(va_arg(ap, int));
	else if (*(s + 1) == 'u')
		count += ft_putnbr_d(va_arg(ap, unsigned int));
	else if (*(s + 1) == 'X')
		count += ft_putnbr_hex_u(va_arg(ap, unsigned int));
	return (count);
}
