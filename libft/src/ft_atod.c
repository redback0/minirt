/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:30:25 by njackson          #+#    #+#             */
/*   Updated: 2024/09/14 15:07:10 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_atod_ext(const char **str)
{
	double	out;

	out = 0;
	while (ft_isdigit(**str))
	{
		out = (out * 10) + (**str - 48);
		(*str)++;
	}
	if (**str == '.')
		(*str)++;
	return (out);
}

double	ft_atod(const char *str)
{
	double	out;
	int		sign;
	int		dec;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	out = ft_atod_ext(&str);
	dec = 0;
	while (ft_isdigit(*str))
	{
		out = (out * 10) + (*str - 48);
		dec++;
		str++;
	}
	return (sign * (out / pow(10, dec)));
}
