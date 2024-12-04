/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:43:03 by nlehmeye          #+#    #+#             */
/*   Updated: 2024/12/03 20:25:35 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_input(const char *file, t_scene *scene, t_mrt_dat *dat)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		ft_err("Open file error", dat);
	line = get_next_line(fd);
	while (line)
	{
		id_assign(line, scene, dat);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	id_assign(char *line, t_scene *scene, t_mrt_dat *dat)
{
	char	**elements;

	elements = ft_split(line, ' ');
	if (!elements || elements[0][0] == '\n')
		return ;
	else if (!ft_strncmp(elements[0], "A", 1))
		assign_A(elements, scene, dat);
	else if (!ft_strncmp(elements[0], "C", 1))
		assign_C(elements, scene, dat);
	else if (!ft_strncmp(elements[0], "L", 1))
		assign_L(elements, scene, dat);
	else if (!ft_strncmp(elements[0], "pl", 2))
		assign_pl(elements, scene, dat);
	else if (!ft_strncmp(elements[0], "sp", 2))
		assign_sp(elements, scene, dat);
	else if (!ft_strncmp(elements[0], "cy", 2))
		assign_cy(elements, scene, dat);
	else
		ft_err("Non-element type present in .rt file.", dat);
	ft_split_free(elements, free);
}

void	assign_vector(char *elementinfo, t_vec3 *vector, t_mrt_dat *dat)
{
	char **xyz;

	xyz = ft_split(elementinfo, ',');
	if (count_array_rows((void **)xyz) != 3)
		return (ft_err("Incorrect vector format.", dat));
	vector->x = ft_atod(xyz[0]);
	vector->y = ft_atod(xyz[1]);
	vector->z = ft_atod(xyz[2]);
}

void	assign_colour(char *elementinfo, t_colour *rgb, t_mrt_dat *dat)
{
	char **colour_info;

	colour_info = ft_split(elementinfo, ',');
	if (count_array_rows((void **)colour_info) != 3)
		return (ft_err("Incorrect colour format.", dat));
	rgb->red = ft_atoi(colour_info[0]);
	rgb->green = ft_atoi(colour_info[1]);
	rgb->blue = ft_atoi(colour_info[2]);
	check_colour_range(*rgb, dat);
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
	return(total_rows);
}
