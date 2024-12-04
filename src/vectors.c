/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:11:33 by njackson          #+#    #+#             */
/*   Updated: 2024/12/04 11:04:05 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec3_dot_product(t_vec3 a, t_vec3 b)
{
	double	out;

	out = a.x * b.x;
	out += a.y * b.y;
	out += a.z * b.z;
	return (out);
}

t_vec3	vec3_cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	out;

	out.x = a.y * b.z - a.z * b.y;
	out.y = a.z * b.x - a.x * b.z;
	out.z = a.x * b.y - a.y * b.x;
	return (out);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vec3	vec3_inverse(t_vec3 a)
{
	a.x = -a.x;
	a.y = -a.y;
	a.z = -a.z;
	return (a);
}

t_vec3	vec3_reflect(t_vec3 a, t_vec3 r)
{
	double	proj;

	proj = 2 * vec3_dot_product(a, r);
	a.x -= r.x * proj;
	a.y -= r.y * proj;
	a.z -= r.z * proj;
	return (a);
}
