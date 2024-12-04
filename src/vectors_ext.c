/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:16:52 by njackson          #+#    #+#             */
/*   Updated: 2024/12/04 11:03:55 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_normalise(t_vec3 a)
{
	double	m;

	m = sqrt(vec3_dot_product(a, a));
	a.x /= m;
	a.y /= m;
	a.z /= m;
	return (a);
}
