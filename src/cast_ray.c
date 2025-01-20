/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:02:13 by nlehmeye          #+#    #+#             */
/*   Updated: 2025/01/15 22:58:25 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		if (hit.obj == NULL || (temp_hit.obj != NULL
				&& temp_hit.cam_dist < hit.cam_dist))
			hit = temp_hit;
		objs = objs->next;
	}
	return (hit);
}
