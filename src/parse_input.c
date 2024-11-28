/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:43:03 by nlehmeye          #+#    #+#             */
/*   Updated: 2024/11/04 11:43:05 by nlehmeye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_input(const char *file, t_scene scene)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		ft_err("Open file error");
	line = get_next_line(fd);
	while (line)
	{
		id_assign(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
}

void	id_assign(char *line, t_scene scene)
{
	char	**elements;

	elements = ft_split(line, ' ');
	if (!elements || elements[0][0] == '\n')
		return ;
	else if (!ft_strncmp(elements[0], "A", 1))
		assign_A(elements, scene);
	else if (!ft_strncmp(elements[0], "C", 1))
		assign_C(elements, scene);
	else if (!ft_strncmp(elements[0], "L", 1))
		assign_L(elements, scene);
	else if (!ft_strncmp(elements[0], "pl", 2))
		assign_pl(elements, scene);
	else if (!ft_strncmp(elements[0], "sp", 2))
		assign_sp(elements, scene);
	else if (!ft_strncmp(elements[0], "cy", 2))
		assign_cy(elements, scene);
	else
		ft_err("Non-element type present in scene file");
	ft_split_free(elements, free);
	ft_printf("%s", line);
}
