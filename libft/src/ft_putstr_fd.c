/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:02:21 by njackson          #+#    #+#             */
/*   Updated: 2024/03/25 15:38:05 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	size_t	i;

	if (str)
	{
		i = ft_strlen(str);
		if (write(fd, str, i) < 0)
			return (-1);
		return (i);
	}
	if (write(fd, "(null)", 6) < 0)
		return (-1);
	return (6);
}
