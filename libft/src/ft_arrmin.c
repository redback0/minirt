/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:51:22 by njackson          #+#    #+#             */
/*   Updated: 2024/04/08 17:04:12 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrmin(int *arr, int size)
{
	int	out;

	out = --size;
	while (size-- > 0)
		if (arr[out] >= arr[size])
			out = size;
	return (out);
}
