/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:16:30 by njackson          #+#    #+#             */
/*   Updated: 2024/03/21 11:29:06 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*out;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	out = (char *)malloc(len * sizeof(char));
	if (!out)
		return (0);
	ft_strlcpy(out, s1, len);
	ft_strlcat(out, s2, len);
	return (out);
}
