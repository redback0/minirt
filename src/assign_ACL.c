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

void	assign_A(char **elements, t_scene *scene, t_mrt_dat *dat)
{
	t_alight	alight;

	alight = scene->alight;
	if (count_array_rows((void **)elements) != 3)
		return (ft_err("Incorrect number of element A info.", dat));
	alight.ratio = ft_atod(elements[1]);
	check_unit(alight.ratio, dat);
	assign_colour(elements[2], &alight.colour, dat);
	// printf("%s\n", elements[0]);
	// printf("BRIGHTNESS:   %f\n", alight.ratio);
	// printf("COLOUR:   R: %d, G: %d, B: %d\n\n", alight.colour.red, alight.colour.green, alight.colour.blue);
}

void	assign_C(char **elements, t_scene *scene, t_mrt_dat *dat)
{
	t_cam	camera;

	camera = scene->cam;
	if (count_array_rows((void **)elements) != 4)
		return (ft_err("Incorrect number of element C info.", dat));
	assign_vector(elements[1], &camera.pos, dat);
	assign_vector(elements[2], &camera.angle, dat);
	check_sym_unit(camera.angle, dat);
	camera.fov = ft_atoi(elements[3]);
	check_fov(camera.fov, dat);
	// printf("POSITION: %f\n %f\n %f\n\n", camera.pos.x, camera.pos.y, camera.pos.z);
	// printf("ANGLE: %f\n %f\n %f\n\n", camera.angle.x, camera.angle.y, camera.angle.z);
	// printf("FOV: %d\n\n", camera.fov);
}

void	assign_L(char **elements, t_scene *scene, t_mrt_dat *dat)
{
	t_light light;

	light = scene->light;
	if (count_array_rows((void **)elements) != 4)
		return (ft_err("Incorrect number of element L info.", dat));
	assign_vector(elements[1], &light.pos, dat);
	light.ratio = ft_atod(elements[2]);
	check_unit(light.ratio, dat);
	assign_colour(elements[3], &light.colour, dat);
	// printf("%s\n", elements[0]);
	// printf("POSITION:   X: %f, Y: %f, Z: %f", light.pos.x, light.pos.y, light.pos.z);
	// printf("BRIGHTNESS:   %f\n", light.ratio);
	// printf("COLOUR:   R: %d, G: %d, B: %d\n\n", light.colour.red, light.colour.green, light.colour.blue);
}
