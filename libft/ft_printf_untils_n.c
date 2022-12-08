/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_untils_n.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:51:26 by psuanpro          #+#    #+#             */
/*   Updated: 2022/05/23 03:05:43 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	unsigned int	nbr;
	int				len;

	len = 0;
	if (n < 0)
	{
		len++;
		nbr = n * -1;
		write(1, "-", 1);
	}
	else
		nbr = n;
	if (nbr > 9)
		len += ft_putnbr(nbr / 10);
	len += ft_putchar(nbr % 10 + '0');
	return (len);
}

int	ft_putnbr_d(unsigned int n)
{
	unsigned int	nbr;
	int				count;

	count = 0;
	nbr = n;
	if (nbr > 9)
		count += ft_putnbr(nbr / 10);
	count += ft_putchar(nbr % 10 + '0');
	return (count);
}

int	ft_putnbr_hex_p(size_t nbr)
{
	int	count;

	count = 0;
	if (nbr > 15)
		count += ft_putnbr_hex_p(nbr / 16);
	count += write(1, &"0123456789abcdef"[nbr % 16], 1);
	return (count);
}

int	ft_putnbr_hex(size_t nbr)
{
	int	count;

	count = 0;
	if (nbr > 15)
		count += ft_putnbr_hex(nbr / 16);
	count += write(1, &"0123456789abcdef"[nbr % 16], 1);
	return (count);
}

int	ft_putnbr_hex_u(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr > 15)
		count += ft_putnbr_hex_u(nbr / 16);
	count += write(1, &"0123456789ABCDEF"[nbr % 16], 1);
	return (count);
}
