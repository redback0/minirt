/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:23:38 by njackson          #+#    #+#             */
/*   Updated: 2025/01/20 12:40:57 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// top is the cap on the positon, bottom is the cap at pos + (angle * height)
static t_hit	cast_ray_cylinder_caps(t_cylinder *obj, t_ray ray)
{
	t_hit	out;
	t_obj	phony;
	t_vec3	relative;
	int		is_top_first;

	phony = *obj;
	is_top_first = vec3_dot(obj->angle, ray.dir) > 0;
	if (is_top_first)
		phony.pos = vec3_add(obj->pos, vec3_mult(obj->angle, -obj->height / 2));
	else
		phony.pos = vec3_add(obj->pos, vec3_mult(obj->angle, obj->height / 2));
	out = cast_ray_plane(&phony, ray);
	relative = vec3_sub(out.point, phony.pos);
	if (out.obj && fabs(vec3_dot(relative, relative)) < pow(obj->radius, 2))
		return (out.obj = obj, out);
	if (is_top_first)
		phony.pos = vec3_add(obj->pos, vec3_mult(obj->angle, obj->height / 2));
	else
		phony.pos = vec3_add(obj->pos, vec3_mult(obj->angle, -obj->height / 2));
	out = cast_ray_plane(&phony, ray);
	relative = vec3_sub(out.point, phony.pos);
	if (out.obj && fabs(vec3_dot(relative, relative)) < pow(obj->radius, 2))
		return (out.obj = obj, out);
	return ((t_hit){.obj = NULL});
}

static t_hit	cast_ray_cylinder_alt(t_cylinder *obj,
	t_ray ray, t_cy_hit_info cy)
{
	t_hit	hit;

	hit = cast_ray_cylinder_caps(obj, ray);
	if (hit.obj)
		return (hit);
	if (cy.r_dist + cy.r_offset >= ray.max_dist
		|| cy.o_dist + cy.o_offset < -obj->height / 2
		|| cy.o_dist + cy.o_offset > obj->height / 2)
		return ((t_hit){.obj = NULL});
	hit.cam_dist = cy.r_dist + cy.r_offset;
	hit.point = vec3_add(ray.start, vec3_mult(ray.dir, hit.cam_dist));
	hit.obj = obj;
	hit.normal = vec3_normalise(vec3_sub(vec3_add(obj->pos,
					vec3_mult(obj->angle, cy.o_dist + cy.o_offset)),
				hit.point));
	return (hit);
}

/*
cylinder hit
adir     -> perpendicular to obj->angle and ray.dir
a        -> minimum distance between obj axis and ray axis
b        -> other part of a triangle to the outside of the circle
cosphi   -> sin of the angle between obj->angle and ray.dir, and the cosine of
             the angle between bdir(undefined here) and obj->angle
r_offset -> distance back (or forward) along obj->angle to get to the hit.point
o_offset -> offset for the hit point cast onto the cylinder axis
r_dist   -> distance from ray.start along ray.dir to get to the midpoint of 2
             possible hit.points.
o_dist   -> distance from obj->pos to the point inbetween the 2 possible hit
             points along obj->angle
hit      -> information about the intersection -- point, obj, normal, cam_dist
*/
static t_hit	cast_ray_cylinder_hit(t_cylinder *obj, t_ray ray,
	t_cy_hit_info cy)
{
	t_hit	hit;

	if (cy.r_dist + cy.r_offset <= 0.00001
		|| cy.r_dist - cy.r_offset >= ray.max_dist
		|| cy.o_dist + fabs(cy.o_offset) < -obj->height / 2
		|| cy.o_dist - fabs(cy.o_offset) > obj->height / 2)
		return ((t_hit){.obj = NULL});
	if (cy.r_dist - cy.r_offset <= 0
		|| cy.o_dist - cy.o_offset < -obj->height / 2
		|| cy.o_dist - cy.o_offset > obj->height / 2)
		return (cast_ray_cylinder_alt(obj, ray, cy));
	hit.cam_dist = cy.r_dist - cy.r_offset;
	hit.point = vec3_add(ray.start, vec3_mult(ray.dir, hit.cam_dist));
	hit.obj = obj;
	hit.normal = vec3_normalise(vec3_sub(hit.point,
				vec3_add(obj->pos, vec3_mult(obj->angle,
						cy.o_dist - cy.o_offset))));
	return (hit);
}

t_hit	cast_ray_cylinder(t_cylinder *obj, t_ray ray)
{
	t_vec3			adir;
	double			a;
	double			b;
	double			dot_adir;
	t_cy_hit_info	cy;

	adir = vec3_cross(obj->angle, ray.dir);
	dot_adir = vec3_dot(adir, adir);
	if (dot_adir < 0)
		return (cast_ray_cylinder_caps(obj, ray));
	a = vec3_dot(vec3_normalise(adir), vec3_sub(ray.start, obj->pos));
	if (fabs(a) > obj->radius)
		return ((t_hit){.obj = NULL});
	b = sqrt(pow(obj->radius, 2) - pow(a, 2));
	cy.r_offset = b / sqrt(dot_adir);
	cy.r_dist = -vec3_dot(vec3_cross(obj->angle, adir), vec3_sub(obj->pos,
				ray.start)) / dot_adir;
	cy.o_dist = vec3_dot(vec3_cross(ray.dir, adir), vec3_sub(ray.start,
				obj->pos)) / dot_adir;
	cy.o_offset = vec3_dot(obj->angle, vec3_mult(ray.dir, cy.r_offset));
	return (cast_ray_cylinder_hit(obj, ray, cy));
}
