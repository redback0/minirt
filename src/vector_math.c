/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:30:38 by njackson          #+#    #+#             */
/*   Updated: 2024/10/14 15:36:21 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	v3_normalize(const t_vec3 *v)
{
	double	d;

	d = hypot(v->x, hypot(v->y, v->z));
	return ((t_vec3){.x = v->x / d, .y = v->y / d, .z = v->z / d});
}

double	v3_dot_product(const t_vec3 *a, const t_vec3 *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}
