/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:05:19 by njackson          #+#    #+#             */
/*   Updated: 2024/05/30 12:17:34 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// I want to try a different method of this at some point:
// dup string
// set all delimiters that occur in s to '\0'
// malloc area for required pointers
// set pointers to the locations required
// written below; it works, but it won't pass, as the memory is all freed by
// the first pointer

/*
char	**ft_split(char const *s, char c)
{
	char	**out;
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	if (j < 1)
		return (0);
	out = (char **)malloc((j + 1) * sizeof(char *));
	str = ft_strdup(s);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && s[i] == c)
			str[i++] = '\0';
		if (str[i] == '\0')
			break;
		out[j++] = str + i;
		while (str[i] && str[i] != c)
			i++;
	}
	out[j] = 0;
	return (out);
}
*/

static char	**ft_split_alloc(char const *s, char c, size_t *x)
{
	size_t	i;
	size_t	j;
	char	**out;

	i = 0;
	j = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	out = (char **)malloc((j + 1) * sizeof(char *));
	if (!out)
		return (0);
	out[j] = 0;
	return ((*x = -1), out);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	size_t	i;
	size_t	j;

	out = ft_split_alloc(s, c, &j);
	while (out && s && *s)
	{
		if (*s++ != c)
		{
			s--;
			i = 0;
			while (s[i] && s[i] != c)
				i++;
			out[++j] = ft_substr(s, 0, i);
			if (!out[j])
			{
				while (j > 0)
					free(out[--j]);
				free(out);
				return (0);
			}
			s += i;
		}
	}
	return (out);
}
