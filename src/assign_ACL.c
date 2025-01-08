/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_ACL.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:42:32 by nlehmeye          #+#    #+#             */
/*   Updated: 2024/12/03 20:16:53 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	assign_a(char **elements, t_scene *scene)
{
	t_alight	alight;
	int			err;

	err = 0;
	alight = scene->alight;
	if (count_array_rows((void **)elements) != 3)
	{
		printf("Error\nIncorrect number of element A info.\n");
		return (1);
	}
	alight.ratio = ft_atod_strict(elements[1], &err);
	if (err != 0)
		printf("Error\n atod Error in attempt to assign A.\n");
	err += check_unit(alight.ratio);
	err += assign_colour(elements[2], &alight.colour);
	return (err);
}

int	assign_c(char **elements, t_scene *scene)
{
	t_cam	camera;
	int		err;

	err = 0;
	camera = scene->cam;
	if (count_array_rows((void **)elements) != 4)
	{
		printf("Error\n Incorrect number of element C info.\n");
		return (1);
	}
	err += assign_vector(elements[1], &camera.pos);
	err += assign_vector(elements[2], &camera.angle);
	err += check_sym_unit(camera.angle);
	camera.fov = ft_atoi_strict(elements[3], &err);
	if (err != 0)
		printf("Error\n atod Error in attempt to assign C.\n");
	err += check_fov(camera.fov);
	return (err);
}

int	assign_l(char **elements, t_scene *scene)
{
	t_light	light;
	int		err;

	err = 0;
	light = scene->light;
	if (count_array_rows((void **)elements) != 4)
	{
		printf("Error\n Incorrect number of element L info.\n");
		return (1);
	}
	err += assign_vector(elements[1], &light.pos);
	light.ratio = ft_atod_strict(elements[2], &err);
	if (err != 0)
		printf("Error\natod Error in attempt to assign L.\n");
	err += check_unit(light.ratio);
	err += assign_colour(elements[3], &light.colour);
	return (err);
}

int	assign_vector(char *elementinfo, t_vec3 *vector)
{
	char	**xyz;
	int		static_err;

	static_err = 0;
	xyz = ft_split(elementinfo, ',');
	if (count_array_rows((void **)xyz) != 3)
	{
		printf("Error\nIncorrect vector format.\n");
		ft_split_free(xyz, free);
		return (1);
	}
	vector->x = ft_atod_strict(xyz[0], &static_err);
	vector->y = ft_atod_strict(xyz[1], &static_err);
	vector->z = ft_atod_strict(xyz[2], &static_err);
	ft_split_free(xyz, free);
	if (static_err != 0)
	{
		printf("Error\natod Error in attempt to assign vector.\n");
		return (1);
	}
	return (0);
}

int	assign_colour(char *elementinfo, t_colour *rgb)
{
	char	**colour_info;
	int		static_err;

	static_err = 0;
	colour_info = ft_split(elementinfo, ',');
	if (count_array_rows((void **)colour_info) != 3)
	{
		printf("Error\nIncorrect colour format.\n");
		ft_split_free(colour_info, free);
		return (1);
	}
	rgb->red = ft_atoi_strict(colour_info[0], &static_err);
	rgb->green = ft_atoi_strict(colour_info[1], &static_err);
	rgb->blue = ft_atoi_strict(colour_info[2], &static_err);
	static_err += check_colour_range(*rgb);
	ft_split_free(colour_info, free);
	if (static_err != 0)
	{
		printf("Error\natoi Error in attempt to assign colour.\n");
		return (1);
	}
	return (0);
}
