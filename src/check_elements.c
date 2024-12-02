/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:57:31 by nlehmeye          #+#    #+#             */
/*   Updated: 2024/12/02 14:57:33 by nlehmeye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_sym_unit(t_vec3 angle)
{
	if ((angle.x < -1 || angle.x > 1) ||(angle.y < -1 || angle.y > 1) || (angle.z < -1 || angle.z > 1))
		return (ft_err("Angle outside symmetrical unit range."));
}

void	check_unit(double ratio)
{
	if ((ratio < 0 || ratio > 1))
		return (ft_err("Ratio outside unit range."));
}

void	check_colour_range(t_colour rgb)
{
	if ((rgb.red < 0 || rgb.red > 255) || (rgb.green < 0 || rgb.green > 255) || (rgb.blue < 0 || rgb.blue > 255))
		return (ft_err("RBG outside 0-255 range."));
}

void	check_positive(double obj_dimensions)
{
	if (obj_dimensions <=0)
		return (ft_err("Object dimension values not positive."));
}

void	check_fov(int fov)
{
	if (fov < 1 || fov >359)
		return (ft_err("FOV outside range."));
}