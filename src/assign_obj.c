/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:15:28 by nlehmeye          #+#    #+#             */
/*   Updated: 2024/12/03 20:26:54 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	assign_pl(char **elements, t_scene *scene, t_mrt_dat *dat)
{
	t_obj	*plane;
	t_list	*obj;
	
	plane = malloc(sizeof(*plane));
	if (!plane)
		return (ft_err("Plane Malloc Failed.", dat));
	obj = ft_lstnew((void *)plane);
	ft_lstadd_front(&scene->objs, obj);
	ft_bzero(plane, sizeof(*plane));
	if (count_array_rows((void **)elements) != 4)
		return (ft_err("Incorrect number of element pl info.", dat));
	plane->id = PLANE;
	assign_vector(elements[1], &plane->pos, dat);
	assign_vector(elements[2], &plane->angle, dat);
	check_sym_unit(plane->angle, dat);
	assign_colour(elements[3], &plane->colour, dat);
	// printf("%s\n", elements[0]);
	// printf("POSITION:   X: %f, Y: %f, Z: %f\n", plane->pos.x, plane->pos.y, plane->pos.z);
	// printf("ANGLE:   X: %f, Y: %f, Z: %f\n", plane->angle.x, plane->angle.y, plane->angle.z);
	// printf("COLOUR:   R: %d, G: %d, B: %d\n\n", plane->colour.red, plane->colour.green, plane->colour.blue);
}

void	assign_sp(char **elements, t_scene *scene, t_mrt_dat *dat)
{
	t_obj	*sphere;
	t_list	*obj;
	int		err;

	err = 0;
	sphere = malloc(sizeof(*sphere));
	if (!sphere)
		return (ft_err("Sphere Malloc Failed.", dat));
	obj = ft_lstnew((void *)sphere);
	ft_lstadd_front(&scene->objs, obj);
	ft_bzero(sphere, sizeof(*sphere));
	if (count_array_rows((void **)elements) != 4)
		return (ft_err("Incorrect number of element sp info", dat));
	sphere->id = SPHERE;
	assign_vector(elements[1], &sphere->pos, dat);
	sphere->diameter = ft_atod_strict(elements[2], &err);
	check_positive(sphere->diameter, dat);
	assign_colour(elements[3], &sphere->colour, dat);
	if (err != 0)
		return (ft_err("atod Error in attempt to assign sphere.", dat));
	// printf("%s\n", elements[0]);
	// printf("POSITION:   X: %f, Y: %f, Z: %f\n", sphere->pos.x, sphere->pos.y, sphere->pos.z);
	// printf("DIAMETER:  %f\n", sphere.diameter);
	// printf("COLOUR:   R: %d, G: %d, B: %d\n\n", sphere->colour.red, sphere->colour.green, sphere->colour.blue);
}

void	assign_cy(char **elements, t_scene *scene, t_mrt_dat *dat)
{
	t_obj	*cylinder;
	t_list	*obj;
	int		err;

	err = 0;
	cylinder = malloc(sizeof(*cylinder));
	if (!cylinder)
		return (ft_err("Cylinder Malloc Failed.", dat));
	obj = ft_lstnew((void *)cylinder);
	ft_lstadd_front(&scene->objs, obj);
	ft_bzero(cylinder, sizeof(*cylinder));
	if (count_array_rows((void **)elements) != 6)
		return (ft_err("Incorrect number of element cy info", dat));
	cylinder->id = CYLINDER;
	assign_vector(elements[1], &cylinder->pos, dat);
	assign_vector(elements[2], &cylinder->angle, dat);
	check_sym_unit(cylinder->angle, dat);
	cylinder->diameter = ft_atod_strict(elements[3], &err);
	check_positive(cylinder->diameter, dat);
	cylinder->height = ft_atod_strict(elements[4], &err);
	check_positive(cylinder->height, dat);
	assign_colour(elements[5], &cylinder->colour, dat);
	if (err != 0)
		return (ft_err("atod Error in attempt to assign cylinder.", dat));
	// printf("%s\n", elements[0]);
	// printf("POSITION:   X: %f, Y: %f, Z: %f\n", cylinder.pos.x, cylinder.pos.y, cylinder.pos.z);
	// printf("ANGLE:   X: %f, Y: %f, Z: %f\n", cylinder.angle.x, cylinder.angle.y, cylinder.angle.z);
	// printf("DIAMETER:  %f\n", cylinder.diameter);
	// printf("HEIGHT:  %f\n", cylinder.height);
	// printf("COLOUR:   R: %d, G: %d, B: %d\n\n", cylinder.colour.red, cylinder.colour.green, cylinder.colour.blue);
}