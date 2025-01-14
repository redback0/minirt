/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:02:13 by nlehmeye          #+#    #+#             */
/*   Updated: 2025/01/14 15:01:43 by njackson         ###   ########.fr       */
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
		if (hit.obj == NULL || (temp_hit.obj != NULL && temp_hit.cam_dist < hit.cam_dist))
			hit = temp_hit;
		objs = objs->next;
	}
	return (hit);
}
//  -- CAST_RAY_SPHERE() --

t_hit	cast_ray_sphere(t_obj *obj, t_ray ray)
{
	t_hit	hit;

	hit.cam_dist = solve_quadratic(obj, ray);
	if (hit.cam_dist == 0)
		return ((t_hit){.obj = NULL});
	hit.obj = obj;
	hit.normal = vec3_mult((vec3_add(hit.point, vec3_inverse(obj->pos))), (1 / obj->radius));
	hit.point = vec3_add(ray.start, (vec3_mult(ray.dir, hit.cam_dist)));
	return ((t_hit){.obj = NULL});
}

double	solve_quadratic(t_obj *obj, t_ray ray)
{
	t_quad	quad;

	quad.a = vec3_dot(ray.dir, ray.dir);
	quad.b = 2 * vec3_dot(vec3_add(ray.start, vec3_inverse(obj->pos)), ray.dir);
	quad.c = vec3_dot(vec3_add(ray.start, vec3_inverse(obj->pos)),
			vec3_add(ray.start, vec3_inverse(obj->pos))) - pow(obj->radius, 2);
	quad.discrim = pow(quad.b, 2) - (4 * quad.a * quad.c);
	if (quad.discrim > 0)
	{
		quad.t1 = (-quad.b + sqrt(quad.discrim)) / (2 * quad.a);
		quad.t2 = (-quad.b - sqrt(quad.discrim)) / (2 * quad.a);
	}
	else if (quad.discrim == 0)
		quad.t1 = -quad.b / (2 * quad.a);
	if (quad.t2 > 0 && quad.t2 < quad.t1)
		quad.t1 = quad.t2;
	if (quad.t1 < 0)
		quad.t1 = 0;
	return (quad.t1);
}
// MAX DISTANCE HANDLING
// find closest point of object, not past [max distance]
// params:
//   t obj object (the type of obj) to check intersects
//   angle direction of ray (normalised)
//   max distance (double, infinity if no max dist)
// returns: closest hit point, as t_hit datatype


//  -- CAST_RAY_PLANE() --
t_hit	cast_ray_plane(t_obj *obj, t_ray ray)
{
	t_hit	hit;
	
	if (vec3_dot(ray.dir, obj->angle) == 0)
		return ((t_hit){.obj = NULL});
	hit.cam_dist = -(vec3_dot(vec3_add(ray.start, vec3_inverse(obj->pos)), obj->angle) / vec3_dot(ray.dir, obj->angle));
	if (hit.cam_dist == 0)
		return ((t_hit){.obj = NULL});
	hit.obj = obj;
	if (vec3_dot(obj->angle, ray.dir) > 0)
		hit.normal = vec3_inverse(obj->angle);
	else
		hit.normal = obj->angle;
	hit.point = vec3_add(ray.start, (vec3_mult(ray.dir, hit.cam_dist)));
	return ((t_hit){.obj = NULL});
}
// find closest point of object, not past [max distance]
// params:
//   t obj object (the type of obj) to check intersects
//   angle direction of ray (normalised)
//   max distance (double, infinity if no max dist)
// returns: closest hit point, as t_hit datatype
