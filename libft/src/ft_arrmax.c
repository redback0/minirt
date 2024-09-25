/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:10:25 by njackson          #+#    #+#             */
/*   Updated: 2024/04/08 21:11:49 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrmax(int *arr, int size)
{
	int	out;

	out = --size;
	while (size-- > 0)
		if (arr[out] <= arr[size])
			out = size;
	return (out);
}
