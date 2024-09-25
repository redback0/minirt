/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:31:36 by njackson          #+#    #+#             */
/*   Updated: 2024/05/15 20:52:26 by njackson         ###   ########.fr       */
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

unsigned int	ft_atou_base(const char *str, char *base)
{
	unsigned int	out;
	int				b;
	int				num;

	if (!ft_strchrdup(base))
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	b = ft_strlen(base);
	out = 0;
	num = (long)ft_strchr(base, *str++) - (long)base;
	while (num < b && num >= 0)
	{
		out = (out * b) + num;
		num = (long)ft_strchr(base, *str++) - (long)base;
	}
	return (out);
}
