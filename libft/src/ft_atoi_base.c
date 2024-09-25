/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:31:36 by njackson          #+#    #+#             */
/*   Updated: 2024/05/15 20:47:55 by njackson         ###   ########.fr       */
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

static int	setvars(int *out, int *sign, int *b, char *base)
{
	*out = 0;
	*sign = 1;
	*b = ft_strlen(base);
	return (ft_strchrdup(base));
}

int	ft_atoi_base(const char *str, char *base)
{
	int	out;
	int	sign;
	int	b;
	int	num;

	if (!setvars(&out, &sign, &b, base))
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	num = (long)ft_strchr(base, *str++) - (long)base;
	while (num < b && num >= 0)
	{
		out = (out * b) + num;
		num = (long)ft_strchr(base, *str++) - (long)base;
	}
	return (sign * out);
}
