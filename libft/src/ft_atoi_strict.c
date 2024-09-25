/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:47:09 by njackson          #+#    #+#             */
/*   Updated: 2024/07/31 17:42:10 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_strict(const char *str, int *err)
{
	int	out;
	int	chkof;
	int	sign;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (*err = 1, 0);
	out = 0;
	while (ft_isdigit(*str))
	{
		chkof = out;
		out = (out * 10) + (*(str++) - 48);
		if (out / 10 != chkof && (sign == 1 || !(out < 0 && out - 1 > 0)))
			return (*err = 1, 0);
	}
	if (*str)
		return (*err = 1, 0);
	return (sign * out);
}
