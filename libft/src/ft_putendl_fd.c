/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:27:55 by njackson          #+#    #+#             */
/*   Updated: 2024/03/25 16:03:14 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	out;

	if (!s)
		return (0);
	out = ft_putstr_fd(s, fd);
	if (out < 0 || ft_putchar_fd('\n', fd) < 0)
		return (-1);
	return (out + 1);
}
