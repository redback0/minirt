/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:28:33 by njackson          #+#    #+#             */
/*   Updated: 2024/04/05 10:48:44 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memswap(void *a, void *b, size_t n)
{
	size_t			i;
	unsigned char	t;
	unsigned char	*aptr;
	unsigned char	*bptr;

	aptr = (unsigned char *)a;
	bptr = (unsigned char *)b;
	i = 0;
	while (i < n)
	{
		t = aptr[i];
		aptr[i] = bptr[i];
		bptr[i] = t;
		i++;
	}
}
