/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:28:29 by njackson          #+#    #+#             */
/*   Updated: 2025/01/14 20:54:43 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

#ifndef M_PI
# define M_PI           3.14159265358979323846  /* pi */
#endif

// *** t_cam REDEFINITION REQUIRED ***
// +double psin
// +double pcos
// +double ysin
// +double ycos
// +double rect_dist

// *** REQUIRES NEW FUNCTION init_camera TO BE RUN BEFORE raytrace_pixel ***

void	init_camera(t_cam *cam)
{
	double	fovr;

	cam->psin = -cam->angle.y;
	cam->pcos = hypot(cam->angle.z, cam->angle.x);
	if (cam->pcos)
	{
		cam->ysin = cam->angle.x / cam->pcos;
		cam->ycos = cam->angle.z / cam->pcos;
	}
	else
	{
		cam->ysin = 0;
		cam->ycos = 1;
	}
	fovr = (double)cam->fov * (M_PI / 180);
	cam->rect_dist = 1 / (tan(fovr / 2));
}

static t_vec3	camera_rotation(t_vec3 v, t_cam cam)
{
	t_vec3	out;

	out.x = v.x * cam.ycos + v.y * cam.ysin * cam.psin
		+ v.z * cam.ysin * cam.pcos;
	out.y = v.y * cam.pcos - v.z * cam.psin;
	out.z = -v.x * cam.ysin + v.y * cam.ycos * cam.psin
		+ v.z * cam.ycos * cam.pcos;
	return (out);
}

static t_colour	get_colour_from_hit(t_scene *scene, t_hit hit, t_ray ray)
{
	t_colour	out;
	double		dot;

	(void)scene;
	dot = vec3_dot(vec3_normalise(hit.normal), ray.dir);
	if (fabs(dot) > 1)
		printf("ERROR: hit vs ray dot to large\n");
	//if (hit.obj->id == SPHERE)
	//	printf("%f, %f, %f\n", hit.normal.x, hit.normal.y, hit.normal.z);
	out.red = fabs(dot) * 255;
	out.blue = 255 - out.red;
	if (dot > 0)
		out.green = 255;
	else
		out.green = 0;
	return (out);
}

t_colour	raytrace_pixel(t_mrt_dat *dat, int x, int y)
{
	t_image	*img;
	t_cam	*cam;
	t_ray	ray;
	t_hit	hit;

	img = &dat->mlx.img;
	cam = &dat->scene.cam;
	ray.dir.x = 2 * (x - ((double)img->width / 2)) / img->width;
	ray.dir.y = -2 * (y - ((double)img->height / 2)) / img->width;
	ray.dir.z = cam->rect_dist;
	ray.dir = camera_rotation(ray.dir, dat->scene.cam);
	ray.dir = vec3_normalise(ray.dir);
	ray.start = cam->pos;
	ray.max_dist = INFINITY;
	hit = cast_ray(dat->scene.objs, ray);
	if (hit.obj)
	{
		// PHONG STUFF
		return (get_colour_from_hit(&dat->scene, hit, ray));
	}
	return ((t_colour){0, 0, 0});
}
