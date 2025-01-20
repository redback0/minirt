/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:28:16 by nlehmeye          #+#    #+#             */
/*   Updated: 2025/01/20 12:28:17 by nlehmeye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	cast_ray_plane(t_obj *obj, t_ray ray)
{
	t_hit	hit;
	double	cos_angle;

	cos_angle = vec3_dot(ray.dir, obj->angle);
	if (cos_angle == 0)
		return ((t_hit){.obj = NULL});
	hit.cam_dist = -(vec3_dot(vec3_add(ray.start, vec3_inverse(obj->pos)),
				obj->angle) / cos_angle);
	if (hit.cam_dist <= 0.00001 || hit.cam_dist > ray.max_dist)
		return ((t_hit){.obj = NULL});
	hit.obj = obj;
	if (cos_angle > 0)
		hit.normal = vec3_normalise(vec3_inverse(obj->angle));
	else
		hit.normal = vec3_normalise(obj->angle);
	hit.point = vec3_add(ray.start, (vec3_mult(ray.dir, hit.cam_dist)));
	return (hit);
}
