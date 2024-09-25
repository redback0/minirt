/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:17:02 by njackson          #+#    #+#             */
/*   Updated: 2024/03/25 15:43:45 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(long long n, int fd)
{
	signed char	sign;
	int			i;
	int			out_num;

	sign = 1;
	out_num = 0;
	if (n < 0)
	{
		if (write(fd, "-", 1) < 0)
			return (-1);
		out_num = 1;
		sign = -1;
	}
	if (n >= 10 || n <= -10)
	{
		i = ft_putnbr_fd(n / (sign * 10), fd);
		if (i < 0)
			return (-1);
		out_num += i;
	}
	if (ft_putchar_fd((sign * (n % 10)) + '0', fd) < 0)
		return (-1);
	return (out_num + 1);
}
