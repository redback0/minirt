/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_base_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:45:40 by njackson          #+#    #+#             */
/*   Updated: 2024/03/25 16:06:33 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strchrdup(char	*str)
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

int	ft_putunbr_base_fd(unsigned long long n, char *base, int fd)
{
	long long	out_num;
	int			b;

	if (!ft_strchrdup(base))
		return (0);
	b = ft_strlen(base);
	out_num = 0;
	if (n >= (unsigned long long)b)
	{
		out_num = ft_putnbr_base_fd(n / b, base, fd);
		if (out_num < 0)
			return (-1);
	}
	if (ft_putchar_fd((base[n % b]), fd) < 0)
		return (-1);
	return (out_num + 1);
}
