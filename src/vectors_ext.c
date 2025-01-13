/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:16:52 by njackson          #+#    #+#             */
/*   Updated: 2025/01/13 14:17:36 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_normalise(t_vec3 a)
{
	double	m;

	m = sqrt(vec3_dot(a, a));
	a.x /= m;
	a.y /= m;
	a.z /= m;
	return (a);
}

t_vec3	vec3_mult(t_vec3 a, double m)
{
	a.x *= m;
	a.y *= m;
	a.z *= m;
	return (a);
}

double	vec3_dist_betw(t_vec3 pos1, t_vec3 pos2)
{
	double	length;
	t_vec3	temp;

	temp = vec3_add(pos1, vec3_inverse(pos2));
	length = sqrt(vec3_dot(temp, temp));
	return (length);
}
