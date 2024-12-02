/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:15:28 by nlehmeye          #+#    #+#             */
/*   Updated: 2024/11/05 12:15:30 by nlehmeye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	assign_pl(char **elements, t_scene scene)
{
	//FOR NATE, TUES 3/12 MORNING - Pls help, idk what is wrong with my line 21 and 22.
	// Everything else pretty much works, and has been tested. The objects are just not in a linked list.
	//The functions in this file all don't return, but as you can see here I started to play with
	// returning the t_list *obj
	t_obj	plane;
	t_list	*obj;
	
	obj = ft_lstnew((void *)plane);
	ft_lstadd_back(&scene.objs, obj);
	ft_bzero(&plane, sizeof(plane));
	if (count_array_rows((void **)elements) != 4)
		return (ft_err("Incorrect number of element pl info."));
	plane.id = PLANE;
	assign_vector(elements[1], &plane.pos);
	assign_vector(elements[2], &plane.angle);
	check_sym_unit(plane.angle);
	assign_colour(elements[3], &plane.colour);
	// printf("%s\n", elements[0]);
	// printf("POSITION:   X: %f, Y: %f, Z: %f\n", plane.pos.x, plane.pos.y, plane.pos.z);
	// printf("ANGLE:   X: %f, Y: %f, Z: %f\n", plane.angle.x, plane.angle.y, plane.angle.z);
	// printf("COLOUR:   R: %d, G: %d, B: %d\n\n", plane.colour.red, plane.colour.green, plane.colour.blue);
}

void	assign_sp(char **elements, t_scene scene)
{
	t_obj	sphere;
	
	ft_bzero(&sphere, sizeof(sphere));
	if (count_array_rows((void **)elements) != 4)
		return (ft_err("Incorrect number of element sp info"));
	sphere.id = SPHERE;
	assign_vector(elements[1], &sphere.pos);
	sphere.diameter = ft_atod(elements[2]);
	check_positive(sphere.diameter);
	assign_colour(elements[3], &sphere.colour);
	(void)scene;
	// printf("%s\n", elements[0]);
	// printf("POSITION:   X: %f, Y: %f, Z: %f\n", sphere.pos.x, sphere.pos.y, sphere.pos.z);
	// printf("DIAMETER:  %f\n", sphere.diameter);
	// printf("COLOUR:   R: %d, G: %d, B: %d\n\n", sphere.colour.red, sphere.colour.green, sphere.colour.blue);
}

void	assign_cy(char **elements, t_scene scene)
{
	t_obj	cylinder;
	
	ft_bzero(&cylinder, sizeof(cylinder));
	if (count_array_rows((void **)elements) != 6)
		return (ft_err("Incorrect number of element cy info"));
	cylinder.id = CYLINDER;
	assign_vector(elements[1], &cylinder.pos);
	assign_vector(elements[2], &cylinder.angle);
	check_sym_unit(cylinder.angle);
	cylinder.diameter = ft_atod(elements[3]);
	check_positive(cylinder.diameter);
	cylinder.height = ft_atod(elements[4]);
	check_positive(cylinder.height);
	assign_colour(elements[5], &cylinder.colour);
	(void)scene;
	// printf("%s\n", elements[0]);
	// printf("POSITION:   X: %f, Y: %f, Z: %f\n", cylinder.pos.x, cylinder.pos.y, cylinder.pos.z);
	// printf("ANGLE:   X: %f, Y: %f, Z: %f\n", cylinder.angle.x, cylinder.angle.y, cylinder.angle.z);
	// printf("DIAMETER:  %f\n", cylinder.diameter);
	// printf("HEIGHT:  %f\n", cylinder.height);
	// printf("COLOUR:   R: %d, G: %d, B: %d\n\n", cylinder.colour.red, cylinder.colour.green, cylinder.colour.blue);
}


// typedef struct s_obj
// {
// 	t_obj_id	id;
// 	t_pos		pos;
// 	t_colour	colour;
// 	t_angle		angle;
// 	double		diameter;
// 	double		height;
// }	t_obj;