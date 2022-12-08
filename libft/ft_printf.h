/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:32:22 by psuanpro          #+#    #+#             */
/*   Updated: 2022/05/23 16:35:56 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *s, ...);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr(int n);
int		ft_putnbr_d(unsigned int n);
int		ft_ox(void);
int		ft_putnbr_hex_p(size_t nbr);
int		ft_putnbr_hex(size_t nbr);
int		ft_putnbr_hex_u(unsigned int nbr);
int		ft_printf_check(const char *s, va_list ap);

#endif
