/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:28:04 by nlehmeye          #+#    #+#             */
/*   Updated: 2025/01/20 12:28:06 by nlehmeye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	cast_ray_sphere(t_obj *obj, t_ray ray)
{
	t_hit	hit;

	hit.cam_dist = solve_quadratic(obj, ray);
	if (hit.cam_dist == 0 || hit.cam_dist > ray.max_dist)
		return ((t_hit){.obj = NULL});
	hit.obj = obj;
	hit.point = vec3_add(ray.start, (vec3_mult(ray.dir, hit.cam_dist)));
	hit.normal = vec3_normalise(vec3_mult((vec3_add(hit.point,
						vec3_inverse(obj->pos))), (1 / obj->radius)));
	return (hit);
}

double	solve_quadratic(t_obj *obj, t_ray ray)
{
	t_quad	quad;
	t_vec3	obj_pos_to_cam;

	obj_pos_to_cam = vec3_sub(ray.start, obj->pos);
	quad.a = vec3_dot(ray.dir, ray.dir);
	quad.b = 2 * vec3_dot(obj_pos_to_cam, ray.dir);
	quad.c = vec3_dot(obj_pos_to_cam, obj_pos_to_cam) - pow(obj->radius, 2);
	quad.discrim = quad.b * quad.b - 4 * quad.a * quad.c;
	t1_assign(&quad);
	return (quad.t1);
}

void	t1_assign(t_quad *quad)
{
	double	q;

	q = 0.0;
	quad->t1 = 0;
	if (quad->discrim < 0)
		return ;
	else if (quad->discrim == 0)
	{
		quad->t1 = -0.5 * quad->b / quad->a;
		quad->t2 = -0.5 * quad->b / quad->a;
	}
	else
	{
		if (quad->b > 0)
			q = -0.5 * (quad->b + sqrt(quad->discrim));
		else
			q = -0.5 * (quad->b - sqrt(quad->discrim));
	}
	quad->t1 = q / quad->a;
	quad->t2 = quad->c / q;
	if (quad->t2 > 0 && quad->t2 < quad->t1)
		quad->t1 = quad->t2;
	if (quad->t1 < 0)
		quad->t1 = 0;
}
