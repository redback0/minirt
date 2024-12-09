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
		ft_err("Open file error", dat, NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
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
	if (!elements || !elements[0] || elements[0][0] == '\n')
	{
		free(elements);
		return ;
	}
	else if (!ft_strncmp(elements[0], "A", 1))
		assign_A(elements, scene, dat, line);
	else if (!ft_strncmp(elements[0], "C", 1))
		assign_C(elements, scene, dat, line);
	else if (!ft_strncmp(elements[0], "L", 1))
		assign_L(elements, scene, dat, line);
	else if (!ft_strncmp(elements[0], "pl", 2))
		assign_pl(elements, scene, dat, line);
	else if (!ft_strncmp(elements[0], "sp", 2))
		assign_sp(elements, scene, dat, line);
	else if (!ft_strncmp(elements[0], "cy", 2))
		assign_cy(elements, scene, dat, line);
	else
		ft_err("Non-element type present in .rt file.", dat, line);
	ft_split_free(elements, free);
}

void	assign_vector(char *elementinfo, t_vec3 *vector, t_mrt_dat *dat, char *line)
{
	char	**xyz;
	int		err;

	err = 0;
	xyz = ft_split(elementinfo, ',');
	if (count_array_rows((void **)xyz) != 3)
		return (ft_err("Incorrect vector format.", dat, line));
	vector->x = ft_atod_strict(xyz[0], &err);
	vector->y = ft_atod_strict(xyz[1], &err);
	vector->z = ft_atod_strict(xyz[2], &err);
	ft_split_free(xyz, free);
	if (err != 0)
		return (ft_err("atod Error in attempt to assign vector.", dat, line));
}

void	assign_colour(char *elementinfo, t_colour *rgb, t_mrt_dat *dat, char *line)
{
	char	**colour_info;
	int		err;

	err = 0;
	colour_info = ft_split(elementinfo, ',');
	if (count_array_rows((void **)colour_info) != 3)
		return (ft_err("Incorrect colour format.", dat, line));
	rgb->red = ft_atoi_strict(colour_info[0], &err);
	rgb->green = ft_atoi_strict(colour_info[1], &err);
	rgb->blue = ft_atoi_strict(colour_info[2], &err);
	check_colour_range(*rgb, dat, line);
	ft_split_free(colour_info, free);
	if (err != 0)
		return (ft_err("atoi Error in attempt to assign colour.", dat, line));
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
