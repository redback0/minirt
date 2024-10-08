/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:27:31 by njackson          #+#    #+#             */
/*   Updated: 2024/10/08 14:35:15 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_atod_strict_ext(const char **str, int *err)
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
	else if (**str)
		*err = 1;
	return (out);
}

double	ft_atod_strict(const char *str, int *err)
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
	out = ft_atod_strict_ext(&str, err);
	dec = 0;
	while (ft_isdigit(*str))
	{
		out = (out * 10) + (*str - 48);
		dec++;
		str++;
	}
	if (*str)
		*err = 1;
	return (sign * (out / pow(10, dec)));
}
