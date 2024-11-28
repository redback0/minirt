/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_A.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:42:32 by nlehmeye          #+#    #+#             */
/*   Updated: 2024/11/05 13:42:33 by nlehmeye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// How do we refer to each object in the scene, attaching it to the scene.
// Initialise a struct?
t_alight	assign_A(char **elements, t_scene scene)
{
	char **rgb;
	t_alight alight;
	if (elements[3])
		return (ft_err("Too much A element info"));
	alight.ratio = ft_atod(elements[1]);
	rgb = ft_split(elements[3], ',');
	alight.colour.red = ft_atoi(rgb[0]);
	alight.colour.blue = ft_atoi(rgb[1]);
	alight.colour.green = ft_atoi(rgb[2]);
	ft_printf("%s\n", elements[0]);
	
	return (alight);
}

// assign_A_test
