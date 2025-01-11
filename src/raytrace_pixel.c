/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:28:29 by njackson          #+#    #+#             */
/*   Updated: 2025/01/11 16:17:23 by njackson         ###   ########.fr       */
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

t_colour	raytrace_pixel(t_mrt_dat *dat, int x, int y)
{
	t_ray		ray;
	t_intersect	hit;

	ray.dir.x = 2 * (x - (dat->mlx.img.width / 2)) / dat->mlx.img.width;
	ray.dir.y = 2 * (y - (dat->mlx.img.height / 2)) / dat->mlx.img.width;
	ray.dir.z = dat->scene.cam.rect_dist;
	ray.dir = camera_rotation(ray.dir, dat->scene.cam);
	ray.dir = vec3_normalise(ray.dir);
	hit = cast_ray(dat->scene.objs, ray);
	if (hit.obj)
	{
		// PHONG STUFF
		return (hit.obj->colour);
	}
	return ((t_colour){0, 0, 0});
}
