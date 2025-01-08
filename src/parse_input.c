/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:43:03 by nlehmeye          #+#    #+#             */
/*   Updated: 2024/12/11 09:19:33 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_input(const char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	int		gnl_err;

	line = NULL;
	gnl_err = 0;
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
	{
		ft_printf("Error:\nOpen file error\n");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		gnl_err += id_assign(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (gnl_err);
}

int	id_assign(char *line, t_scene *scene)
{
	char	**elements;
	int		err;

	err = 0;
	elements = ft_split(line, ' ');
	id_assign_assist(elements, scene, &err);
	ft_split_free(elements, free);
	return (err);
}

void	id_assign_assist(char **elements, t_scene *scene, int *err)
{
	if (!elements || !elements[0] || elements[0][0] == '\n')
		;
	else if (!ft_strncmp(elements[0], "A", 1))
		*err += assign_a(elements, scene);
	else if (!ft_strncmp(elements[0], "C", 1))
		*err += assign_c(elements, scene);
	else if (!ft_strncmp(elements[0], "L", 1))
		*err += assign_l(elements, scene);
	else if (!ft_strncmp(elements[0], "pl", 2))
		*err += assign_pl(elements, scene);
	else if (!ft_strncmp(elements[0], "sp", 2))
		*err += assign_sp(elements, scene);
	else if (!ft_strncmp(elements[0], "cy", 2))
		*err += assign_cy(elements, scene);
	else
	{
		ft_printf("Error:\nNon-element type present in .rt file.\n");
		(*err)++;
	}
}

int	count_array_rows(void **arr)
{
	int	total_rows;

	total_rows = 0;
	while (*arr != NULL)
	{
		total_rows++;
		arr++;
	}
	return (total_rows);
}
