/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:23:38 by njackson          #+#    #+#             */
/*   Updated: 2025/01/13 14:21:56 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
// old version
t_hit	cast_ray_cylinder(t_cylinder *obj,
		t_pos start, t_angle dir, double max_dist)
{
	t_vec3		perp; // a line perpendicula to both obj dir and cam dir
	t_vec3		local; // the cylider pos - the cam pos
	double		sin_theta; // sine of angle between cylinder dir and cam dir
	double		dist_betw; // min dist between cylider line and cam line
	double		remain; // part of point transform
	double		back; // dist back toward obj.pos
	double		dist; // distance from obj.pos along obj.angle
	t_hit	out;

	/ * x * /
	perp = vec3_cross_product(obj->angle, dir);
	/ * len(x) * /
	sin_theta = sqrt(vec3_dot_product(perp, perp));
	if (sin_theta == 0.0)
		return ((t_hit){.obj = NULL});

	/ * normalize(x) * /
	out.normal = vec3_mult(perp, 1 / sin_theta);

	local = vec3_add(obj->pos, vec3_inverse(start));
	/ * a * /
	dist_betw = vec3_dot_product(out.normal, local);
	/ * b * /
	remain = sqrt(pow((obj->diameter / 2), 2) - pow(dist_betw, 2));

	/ * m * /
	back = sqrt(1 - pow(sin_theta, 2)) * remain / sin_theta;
	/ * t * /
	dist = (vec3_dot_product(vec3_cross_product(dir, perp), vec3_inverse(local))
		/ vec3_dot_product(perp, perp) - back);
	if (dist < -(obj->height / 2) || dist > obj->height / 2)
		return ((t_hit){.obj = NULL});
		// need to check end cap, then other wall
	/ * i * /
	out.point = vec3_add(vec3_add(obj->pos, vec3_mult(obj->angle, dist)),
			vec3_add(vec3_mult(out.normal, dist_betw),
			vec3_mult(vec3_cross_product(out.normal, obj->angle), -remain)));
	out.cam_dist = vec3_dot_product(vec3_cross_product(obj->angle, perp)
		vec3_inverse(local)) / vec3_dot_product(perp, perp);
	if (out.cam_dist > max_dist)
		return ((t_hit){.obj = NULL});
	out.obj = obj;
	return (out);
}
*/

// top is the cap on the positon, bottom is the cap at pos + (angle * height)
static t_hit	cast_ray_cylinder_caps(t_cylinder *obj, t_ray ray)
{
	t_hit	out;
	t_obj		phony;
	t_vec3		relative;
	int			is_top_first;

	phony = *obj;
	is_top_first = vec3_dot(obj->angle, ray.dir) > 0;
	if (!is_top_first)
		phony.pos = vec3_add(obj->pos, vec3_mult(obj->angle, obj->height));
	out = cast_ray_plane(&phony, ray);
	relative = vec3_add(out.point, phony.pos);
	if (out.obj
		&& ft_abs(vec3_dot(relative, relative)) < pow(obj->radius, 2))
	{
		out.obj = obj;
		return (out);
	}
	if (is_top_first)
		phony.pos = obj->pos;
	else
		phony.pos = vec3_add(obj->pos, vec3_mult(obj->angle, obj->height));
	out = cast_ray_plane(&phony, ray);
	relative = vec3_add(out.point, phony.pos);
	if (out.obj
		&& ft_abs(vec3_dot(relative, relative)) < pow(obj->radius, 2))
	{
		out.obj = obj;
		return (out);
	}
	return ((t_hit){.obj = NULL});
}

static t_hit	cast_ray_cylinder_alt(t_cylinder *obj, t_ray ray)
{
	(void)obj, (void)ray;

	return ((t_hit){.obj = NULL});
}

/*
parameters
t_obj	obj
{
	t_pos	pos;
	t_angle	angle;
	double	diameter;
	double	height;
	...
}
t_ray	ray
{
	t_pos	start;
	t_angle	dir;
	double	max_dist;
}

return
t_hit
{
	t_point	point;
	t_obj	obj;
	t_angle	normal;
	double	cam_dist;
}
*/

t_hit	cast_ray_cylinder(t_cylinder *obj, t_ray ray)
{
	t_vec3		x_dir;
	t_vec3		y_dir;
	//t_vec3	z_dir; // = obj->angle
	t_vec3		dists; // distances to go along with x_dir, y_dir and obj->angle

	t_vec3		extra;
	// extra.x: the offset distance of the hit
	// extra.y: vec3_dot(x_dir, x_dir)
	// extra.z: sqrt(extra.y);
	t_hit	out;

	// the dir and dists will define an offset from c to find the hit
	// points
	// note, dist.z will be + or - m, dist.y will be positive or negative

	x_dir = vec3_cross(obj->angle, ray.dir);
	extra.y = vec3_dot(x_dir, x_dir);
	if (extra.y == 0)
		return (cast_ray_cylinder_caps(obj, ray));
	extra.z = sqrt(extra.y);
	dists.x = vec3_dot(vec3_mult(x_dir, 1 / extra.z),
			vec3_add(ray.start, vec3_inverse(obj->pos)));
	if (dists.x > pow(obj->radius, 2))
		return ((t_hit){.obj = NULL});
	y_dir = vec3_cross(vec3_mult(x_dir, 1 / extra.z), obj->angle);
	dists.y = sqrt(pow(obj->height / 2, 2) - pow(dists.x, 2));
	dists.z = vec3_dot(vec3_cross(ray.dir, x_dir),
			vec3_add(ray.start, vec3_inverse(obj->pos))) / extra.y;
	extra.x = sqrt(1 - extra.y) * dists.y / extra.z;
	if ((dists.z - extra.x < 0 && dists.z + extra.x < 0)
		&& (dists.z - extra.x > obj->height && dists.z + extra.x > obj->height))
		return ((t_hit){.obj = NULL});
	if (dists.z - extra.x < 0 || dists.z - extra.x > obj->height)
		return (cast_ray_cylinder_alt(obj, ray/*, ???*/));
	out.point = vec3_add(obj->pos, vec3_mult(x_dir, dists.x));
	out.point = vec3_add(out.point, vec3_mult(y_dir, dists.y));
	out.point = vec3_add(out.point, vec3_mult(obj->angle, dists.z - extra.x));
	out.normal = vec3_normalise(vec3_add(out.point, vec3_inverse(vec3_add(
						obj->pos, vec3_mult(obj->angle, dists.z - extra.x)))));
	out.obj = obj;
	return (out);
}
