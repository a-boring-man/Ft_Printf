/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinna <jrinna@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:41:39 by jrinna            #+#    #+#             */
/*   Updated: 2021/12/28 09:10:53 by jrinna           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar_int(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_putstr_int(char *s)
{
	int	i;

	i = -1;
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	while (s[++i])
		ft_putchar_fd(s[i], 1);
	if (i == -1)
		i++;
	return (i);
}

static int	ft_putnbr_base_int(long nbr, char *base, int mode)
{
	unsigned long	unbr;
	int				r;
	int				counter;

	counter = 0;
	if (mode == 0 && nbr < 0)
	{
		unbr = -nbr;
		write(1, "-", 1);
		++counter;
	}
	else
		unbr = *((unsigned long *)(&nbr));
	r = unbr % ft_strlen(base);
	if (unbr >= ft_strlen(base))
	{
		counter += ft_putnbr_base_int((unbr / ft_strlen(base)), base, mode);
	}
	ft_putchar_int(base[r]);
	return (counter + 1);
}

static int	ft_conversion(char i, int *t, va_list ag)
{
	if (i == 'c')
		*t += ft_putchar_int(va_arg(ag, int));
	if (i == 's')
		*t += ft_putstr_int(va_arg(ag, char *));
	if (i == 'd')
		*t += ft_putnbr_base_int(va_arg(ag, int), "0123456789", 0);
	if (i == 'i')
		*t += ft_putnbr_base_int(va_arg(ag, int), "0123456789", 0);
	if (i == 'u')
		*t += ft_putnbr_base_int(va_arg(ag, unsigned int), "0123456789", 0);
	if (i == 'x')
		*t += ft_putnbr_base_int(va_arg(ag, unsigned int),
				"0123456789abcdef", 1);
	if (i == 'X')
		*t += ft_putnbr_base_int(va_arg(ag, unsigned int),
				"0123456789ABCDEF", 1);
	if (i == '%')
		*t += ft_putchar_int('%');
	if (i == 'p')
	{
		*t += ft_putstr_int("0x");
		*t += ft_putnbr_base_int(va_arg(ag, long), "0123456789abcdef", 1);
	}
	return (*t);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		total;
	va_list	argtab;

	va_start(argtab, format);
	i = -1;
	total = 0;
	while (format[++i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			ft_conversion(format[i + 1], &total, argtab);
			i++;
		}
		else
			total += ft_putchar_int(format[i]);
	}
	va_end(argtab);
	return (total);
}
