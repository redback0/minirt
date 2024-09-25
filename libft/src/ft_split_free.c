/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:25:25 by njackson          #+#    #+#             */
/*   Updated: 2024/05/01 17:33:22 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_free(char **arr, void (*del)(void *))
{
	int	i;

	i = 0;
	while (arr[i])
		del(arr[i++]);
	free(arr);
}
