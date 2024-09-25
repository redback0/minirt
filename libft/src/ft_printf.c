/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:50:13 by njackson          #+#    #+#             */
/*   Updated: 2024/05/09 20:42:15 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_format(const char *format, va_list data, size_t *i, int fd)
{
	size_t	out;

	if (format[*i] == 'c')
		out = ft_putchar_fd(va_arg(data, int), fd);
	else if (format[*i] == '%')
		out = ft_putchar_fd('%', fd);
	else if (format[*i] == 's')
		out = ft_putstr_fd(va_arg(data, char *), fd);
	else if (format[*i] == 'p')
		out = ft_putptr_fd(va_arg(data, void *), fd);
	else if (format[*i] == 'd')
		out = ft_putnbr_fd(va_arg(data, int), fd);
	else if (format[*i] == 'i')
		out = ft_putnbr_fd(va_arg(data, int), fd);
	else if (format[*i] == 'u')
		out = ft_putnbr_fd(va_arg(data, unsigned int), fd);
	else if (format[*i] == 'x')
		out = ft_putnbr_base_fd(va_arg(data, unsigned int), HEX_LOWER, fd);
	else if (format[*i] == 'X')
		out = ft_putnbr_base_fd(va_arg(data, unsigned int), HEX_UPPER, fd);
	else
		return (0);
	(*i)++;
	return (out);
}

// Takes a fd, format string, and va_list and outputs to fd similarly to printf
// supported % escapes: %, c, s, p, d, i, u, x, X
// no special escape sequences are supported
// Note that va_end is NOT called for the va_list, it must be done by the caller
int	ft_printf_args(int fd, const char *format, va_list args)
{
	size_t	i;
	ssize_t	fwrote;
	size_t	out;

	i = 0;
	out = 0;
	while (format[i])
	{
		if (format[i++] == '%')
		{
			fwrote = ft_printf_format(format, args, &i, fd);
			if (fwrote < 0)
				return (-1);
			out += fwrote;
		}
		else
		{
			if (write(fd, format + i - 1, 1) < 0)
				return (-1);
			out++;
		}
	}
	va_end(args);
	return (out);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		out;

	va_start(args, format);
	out = ft_printf_args(1, format, args);
	va_end(args);
	return (out);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		out;

	va_start(args, format);
	out = ft_printf_args(fd, format, args);
	va_end(args);
	return (out);
}
