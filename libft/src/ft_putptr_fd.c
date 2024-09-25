/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:32:10 by njackson          #+#    #+#             */
/*   Updated: 2024/04/01 14:34:53 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_fd(void *n, int fd)
{
	int	out;
	int	i;

	out = ft_putstr_fd("0x", fd);
	if (out < 0)
		return (-1);
	i = ft_putunbr_base_fd((size_t)n, HEX_LOWER, fd);
	if (i < 0)
		return (-1);
	return (out + i);
}
