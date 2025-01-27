/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:22:26 by njackson          #+#    #+#             */
/*   Updated: 2025/01/27 13:00:59 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_vec3	g_vec3_up = {.x = 0, .y = 1, .z = 0};

int	try_movement(int key, t_mrt_dat *dat)
{
	t_cam	*cam = &dat->scene.cam;
	t_vec3	to_add;

	switch (key)
	{
	case K_LEFT_ARROW:
		break ;
	case K_RIGHT_ARROW:
		break ;
	case K_UP_ARROW:
		break ;
	case K_DOWN_ARROW:
		break ;
	case K_A:
		to_add = vec3_normalise(vec3_cross(cam->angle, g_vec3_up));
		cam->pos = vec3_add(cam->pos, to_add);
		render_frame(dat);
		break ;
	case K_D:
		to_add = vec3_normalise(vec3_cross(cam->angle, g_vec3_up));
		cam->pos = vec3_sub(cam->pos, to_add);
		render_frame(dat);
		break ;
	case K_W:
		to_add = vec3_normalise((t_vec3){
			.x = cam->angle.x, .y = 0, .z = cam->angle.z});
		cam->pos = vec3_add(cam->pos, to_add);
		render_frame(dat);
		break ;
	case K_S:
		to_add = vec3_normalise((t_vec3){
			.x = cam->angle.x, .y = 0, .z = cam->angle.z});
		cam->pos = vec3_sub(cam->pos, to_add);
		render_frame(dat);
		break ;
	case K_SPACE:
		cam->pos = vec3_add(cam->pos, g_vec3_up);
		render_frame(dat);
		break ;
	case K_LSHIFT:
		cam->pos = vec3_sub(cam->pos, g_vec3_up);
		render_frame(dat);
		break ;
	default:
		return (0);
	}
	return (1);
}
