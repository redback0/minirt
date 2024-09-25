/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:35:44 by njackson          #+#    #+#             */
/*   Updated: 2024/05/27 15:10:38 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_buff(char *sav, char *buf)
{
	char	*out;
	int		s_len;
	int		b_len;
	int		i;

	s_len = ft_strlen(sav);
	b_len = ft_strlen(buf);
	out = (char *)malloc((s_len + b_len + 1) * sizeof(char));
	i = 0;
	while (i < s_len)
	{
		out[i] = sav[i];
		i++;
	}
	while (i - s_len < b_len)
	{
		out[i] = buf[i - s_len];
		i++;
	}
	if (sav)
		free(sav);
	out[i] = 0;
	return (out);
}

static char	*read_buffer(int fd, char *buf, char *sav)
{
	int	bytes;
	int	i;

	i = 0;
	while (1)
	{
		while (sav && sav[i] != '\n' && sav[i])
			i++;
		if (sav && sav[i++] == '\n')
			break ;
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buf);
			if (sav)
				free(sav);
			return (0);
		}
		if (bytes == 0)
			break ;
		buf[bytes] = 0;
		sav = join_buff(sav, buf);
	}
	free(buf);
	return (sav);
}

static char	*ft_str_realloc(char *str)
{
	int		i;
	char	*out;

	i = ft_strlen(str);
	out = malloc(i + 1);
	out[i] = 0;
	i = 0;
	while (str[i])
	{
		out[i] = str[i];
		i++;
	}
	free(str);
	return (out);
}

static char	*split_line(char *line, char **sav)
{
	int		nl_i;
	int		l_len;
	int		i;

	l_len = ft_strlen(line);
	nl_i = 0;
	while (line && line[nl_i] && line[nl_i] != '\n')
		nl_i++;
	if (nl_i >= l_len - 1)
	{
		*sav = 0;
		return (line);
	}
	*sav = (char *)malloc((l_len - nl_i + 1) * sizeof(char));
	i = 0;
	while (i < l_len - nl_i)
	{
		(*sav)[i] = line[nl_i + 1 + i];
		i++;
	}
	(*sav)[i] = 0;
	line[nl_i + 1] = 0;
	line = ft_str_realloc(line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*sav[NUM_FD];
	char		*line;
	char		*buf;

	if (fd < 0 || fd >= 64)
		return (0);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (read(fd, buf, 0) != 0)
	{
		free(buf);
		if (sav[fd])
			free(sav[fd]);
		sav[fd] = 0;
		return (0);
	}
	line = read_buffer(fd, buf, sav[fd]);
	line = split_line(line, &sav[fd]);
	return (line);
}
