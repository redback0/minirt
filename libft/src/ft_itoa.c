/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:59:52 by njackson          #+#    #+#             */
/*   Updated: 2024/03/18 10:48:28 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	log_base_n(int n, int base)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*out;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	i = log_base_n(n, 10);
	if (n < 0)
		out = (char *)ft_calloc((i + 2), sizeof(char));
	else
		out = (char *)ft_calloc((i-- + 1), sizeof(char));
	if (!out)
		return (0);
	if (n < 0)
	{
		out[0] = '-';
		out[i--] = -(n % 10) + '0';
		n /= -10;
	}
	while (n)
	{
		out[i--] = n % 10 + '0';
		n /= 10;
	}
	return (out);
}
