/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:27:27 by psuanpro          #+#    #+#             */
/*   Updated: 2022/05/23 02:42:26 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list		ap;
	int			count;

	count = 0;
	va_start(ap, s);
	while (*s)
	{
		if (*s == '%')
		{
			count += ft_printf_check(s, ap);
			s++;
		}
		else
			count += ft_putchar(*s);
		s++;
	}
	va_end(ap);
	return (count);
}
