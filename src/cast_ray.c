/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:02:13 by nlehmeye          #+#    #+#             */
/*   Updated: 2025/01/11 18:03:17 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//  -- CAST_RAY() --
t_hit	cast_ray(t_list *objs, t_ray ray)
{
	t_hit	hit;
	t_hit	temp_hit;

	ft_bzero(&hit, sizeof(hit));
	while (objs != NULL)
	{
		if (((t_obj *)objs->content)->id == PLANE)
			temp_hit = cast_ray_plane(((t_obj *)objs->content), ray);
		else if (((t_obj *)objs->content)->id == SPHERE)
			temp_hit = cast_ray_sphere(((t_obj *)objs->content), ray);
		else if (((t_obj *)objs->content)->id == CYLINDER)
			temp_hit = cast_ray_cylinder(((t_obj *)objs->content), ray);
		if (temp_hit.cam_dist < hit.cam_dist)
			hit = temp_hit;
		objs = objs->next;
	}
	return (hit);
}
//  -- CAST_RAY_SPHERE() --

t_hit	cast_ray_sphere(t_obj *obj, t_ray ray)
{
	t_hit	hit;

	double	t;

	return ((t_hit){.obj = NULL});
}
t_point	find_intersect_point(double t, t_ray ray)
{
	t_point	point;


	return (point);
}

t_hit	solve_quadratic(t_obj *obj, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	t;

	a = vec3_dot(ray.dir, ray.dir);
	b = 2 * vec3_dot(something, ray.dir);
	c = ;
	t = 
	return (t);
}
// find closest point of object, not past [max distance]
// params:
//   t obj object (the type of obj) to check intersects
//   angle direction of ray (normalised)
//   max distance (double, infinity if no max dist)
// returns: closest hit point, as t_hit datatype


//  -- CAST_RAY_PLANE() --
t_hit	cast_ray_plane(t_obj *obj, t_ray ray)
{
	//t_hit	hit;
	(void)obj, (void)ray;

	return ((t_hit){.obj = NULL});
}
// find closest point of object, not past [max distance]
// params:
//   t obj object (the type of obj) to check intersects
//   angle direction of ray (normalised)
//   max distance (double, infinity if no max dist)
// returns: closest hit point, as t_hit datatype

//typedef struct s_intersect
// {
// 	t_point	point;
// 	t_obj	*obj;
// 	t_angle	normal;
// 	double	cam_dist;
// }	t_hit;
