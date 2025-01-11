/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_ACL.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:42:32 by nlehmeye          #+#    #+#             */
/*   Updated: 2025/01/11 16:55:33 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	assign_a(char **elements, t_scene *scene)
{
	t_alight	alight;
	int			err;

	err = 0;
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
	scene->alight = alight;
	return (err);
}

int	assign_c(char **elements, t_scene *scene)
{
	t_cam	camera;
	int		err;

	err = 0;
	if (count_array_rows((void **)elements) != 4)
	{
		printf("Error\n Incorrect number of element C info.\n");
		return (1);
	}
	err += assign_vector(elements[1], &camera.pos);
	err += assign_vector(elements[2], &camera.angle);
	err += check_angle(&camera.angle);
	err += check_sym_unit(camera.angle);
	camera.fov = ft_atoi_strict(elements[3], &err);
	if (err != 0)
		printf("Error\n atod Error in attempt to assign C.\n");
	err += check_fov(camera.fov);
	scene->cam = camera;
	return (err);
}

int	assign_l(char **elements, t_scene *scene)
{
	t_light	light;
	int		err;

	err = 0;
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
	scene->light = light;
	return (err);
}
