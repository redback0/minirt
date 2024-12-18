/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:23:38 by njackson          #+#    #+#             */
/*   Updated: 2024/12/18 14:58:43 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* MOVE TO vectors_ext.c */
t_vec3	vec3_mult(t_vec3 a, double m)
{
	a.x *= m;
	a.y *= m;
	a.z *= m;
	return (a);
}

t_intersect	cast_ray_cylinder(t_cylinder *obj,
		t_pos start, t_angle dir, double max_dist)
{
	t_vec3		perp; // a line perpendicula to both obj dir and cam dir
	t_vec3		local; // the cylider pos - the cam pos
	double		sin_theta; // sine of angle between cylinder dir and cam dir
	double		dist_betw; // min dist between cylider line and cam line
	double		remain; // part of point transform
	double		back; // dist back toward obj.pos
	double		dist; // distance from obj.pos along obj.angle
	t_intersect	out;

	/* x */
	perp = vec3_cross_product(obj->angle, dir);
	/* len(x) */
	sin_theta = sqrt(vec3_dot_product(perp, perp));
	if (sin_theta == 0.0)
		return ((t_intersect){.obj = NULL});

	/* normalize(x) */
	out.normal = vec3_mult(perp, 1 / sin_theta);

	local = vec3_add(obj->pos, vec3_inverse(start));
	/* a */
	dist_betw = vec3_dot_product(out.normal, local);
	/* b */
	remain = sqrt(pow((obj->diameter / 2), 2) - pow(dist_betw, 2));

	/* m */
	back = sqrt(1 - pow(sin_theta, 2)) * remain / sin_theta;
	/* t */
	dist = (vec3_dot_product(vec3_cross_product(dir, perp), vec3_inverse(local)) / vec3_dot_product(perp, perp) - back);
	if (dist < -(obj->height / 2) || dist > obj->height / 2)
		return ((t_intersect){.obj = NULL}); // need to check end cap, then other wall
	/* i */
	out.point = vec3_add(vec3_add(obj->pos, vec3_mult(obj->angle, dist)),
			vec3_add(vec3_mult(out.normal, dist_betw), vec3_mult(vec3_cross_product(out.normal, obj->angle), -remain)));
	out.cam_dist = vec3_dot_product(vec3_cross_product(obj->angle, perp), vec3_inverse(local)) / vec3_dot_product(perp, perp);
	if (out.cam_dist > max_dist)
		return ((t_intersect){.obj = NULL});
	out.obj = obj;
	return (out);
}
