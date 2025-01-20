/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_colour.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:38:19 by njackson          #+#    #+#             */
/*   Updated: 2025/01/20 11:45:18 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
typedef struct s_ray
{
	t_pos	start;
	t_angle	dir;
	double	max_dist;
}	t_ray;
*/

static t_colour	get_diffuse_light(t_light light, t_hit hit,
	t_ray ray, t_vec3 to_light)
{
	t_colour	out;
	double		intensity;

	(void)ray;
	intensity = vec3_dot(hit.normal, to_light) * light.ratio;
	if (intensity < 0)
		return ((t_colour){.red = 0, .blue = 0, .green = 0});
	out.red = hit.obj->colour.red * intensity;
	out.blue = hit.obj->colour.blue * intensity;
	out.green = hit.obj->colour.green * intensity;
	return (out);
}

t_colour	get_hit_colour(t_scene *scene, t_hit hit, t_ray ray)
{
	t_colour	colour;
	t_colour	temp;
	t_hit		check_obstr;
	t_vec3		to_light;
	double		light_dist;

	colour.red = hit.obj->colour.red * scene->alight.ratio;
	colour.blue = hit.obj->colour.blue * scene->alight.ratio;
	colour.green = hit.obj->colour.green * scene->alight.ratio;
	to_light = vec3_sub(scene->light.pos, hit.point);
	light_dist = sqrt(vec3_dot(to_light, to_light));
	to_light = vec3_mult(to_light, 1 / light_dist);
	check_obstr = cast_ray(scene->objs, (t_ray){.start = hit.point,
			.dir = to_light,
			.max_dist = light_dist});
	if (!check_obstr.obj)
	{
		temp = get_diffuse_light(scene->light, hit, ray, to_light);
		colour.red += temp.red;
		colour.blue += temp.blue;
		colour.green += temp.green;
	}
	return (colour);
}

t_colour	get_hit_normal_visual(t_scene *scene, t_hit hit, t_ray ray)
{
	t_colour	out;

	(void)scene, (void)ray;
	out.red = pow(hit.normal.x, 2) * 255;
	out.blue = pow(hit.normal.y, 2) * 255;
	out.green = pow(hit.normal.z, 2) * 255;
	return (out);
}

t_colour	get_second_hit_colour(t_scene *scene, t_hit hit, t_ray ray)
{
	t_vec3		to_light;
	t_hit		check_obstr;
	double		light_dist;

	(void)ray;
	to_light = vec3_sub(scene->light.pos, hit.point);
	light_dist = sqrt(vec3_dot(to_light, to_light));
	to_light = vec3_mult(to_light, 1 / light_dist);
	check_obstr = cast_ray(scene->objs, (t_ray){.start = hit.point,
			.dir = to_light,
			.max_dist = light_dist});
	if (check_obstr.obj)
		return (check_obstr.obj->colour);
	return ((t_colour){.red = 0, .blue = 0, .green = 0});
}
