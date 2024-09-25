/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:09:04 by njackson          #+#    #+#             */
/*   Updated: 2024/05/15 18:32:03 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// prints or doesn't print a log message to STDIN or STDERR based on level:
// level == 0: always print to STDIN
// level == 1: print to STDIN if DEBUG == 1
// level == 2: always print to STDERR
// level == 3: print to STDERR if DEBUG == 1
// prints with the same format as ft_printf
int	ft_log(int level, const char *format, ...)
{
	va_list	args;
	int		fd;
	int		out;

	if (level % 2 && !DEBUG)
		return (0);
	fd = level / 2 + 1;
	va_start(args, format);
	out = ft_printf_args(fd, format, args);
	va_end(args);
	return (out);
}
