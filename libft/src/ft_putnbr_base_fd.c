/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:17:02 by njackson          #+#    #+#             */
/*   Updated: 2024/05/15 19:33:36 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strchrdup(char *str)
{
	if (!str)
		return (0);
	while (*str && *(str + 1))
	{
		if (ft_strchr(str + 1, *str))
			return (0);
		str++;
	}
	return (1);
}

static int	setvars(signed char *sign, int *out_num, int *b, char *base)
{
	*b = ft_strlen(base);
	*sign = 1;
	*out_num = 0;
	return (ft_strchrdup(base));
}

int	ft_putnbr_base_fd(long long n, char *base, int fd)
{
	signed char	sign;
	int			i;
	int			out_num;
	int			b;

	if (!setvars(&sign, &out_num, &b, base))
		return (-1);
	if (n < 0)
	{
		if (write(fd, "-", 1) < 0)
			return (-1);
		out_num = 1;
		sign = -1;
	}
	if (n >= b || n <= -b)
	{
		i = ft_putnbr_base_fd(n / (sign * b), base, fd);
		if (i < 0)
			return (-1);
		out_num += i;
	}
	if (ft_putchar_fd((sign * base[n % b]), fd) < 0)
		return (-1);
	return (out_num + 1);
}
