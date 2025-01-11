/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:02:13 by nlehmeye          #+#    #+#             */
/*   Updated: 2025/01/08 16:02:14 by nlehmeye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//  -- CAST_RAY() --

t_intersect	cast_ray(t_list *objs, t_vec3 origin, t_vec3 dir, double max_dis, int *err)
{
	t_intersect	*intersection;
	
	intersection = malloc(sizeof(*intersection));
	if (!intersection)
	{
		printf("Error\ncast_ray Error.\n");
		(*err)++;
	}
	while (objs != NULL)
	{
		if (objs->content.id == PLANE)
			intersection = cast_ray_plane();
		else if (objs->content->id == SPHERE)
			intersection = cast_ray_sphere();
		else if (objs->content->id == CYLINDER)
			intersection = cast_ray_cylinder();
		objs = objs->next;
	}
	return (intersection);
}


// find closest point that the ray defined by start
//   and dir intersects with using the object type
//   specific functions, returning it along with the object
// params:
//   list of t_objs
//   position of start of ray
//   angle direction of ray (normalised)
//   max distance (double, infinity if no max distance)
// call: cast_ray cylinder/sphere/plane, as we go down the list of t objs
// returns: closest intersection point, as t_intersect datatype


//  -- CAST_RAY_SPHERE() --

// find closest point of object, not past [max distance]
// params:
//   t obj object (the type of obj) to check intersects
//   angle direction of ray (normalised)
//   max distance (double, infinity if no max dist)
// returns: closest intersection point, as t_intersect datatype


//  -- CAST_RAY_PLANE() --

// find closest point of object, not past [max distance]
// params:
//   t obj object (the type of obj) to check intersects
//   angle direction of ray (normalised)
//   max distance (double, infinity if no max dist)
// returns: closest intersection point, as t_intersect datatype

//typedef struct s_intersect
// {
// 	t_point	point;
// 	t_obj	*obj;
// 	t_angle	normal;
// 	double	cam_dist;
// }	t_intersect;