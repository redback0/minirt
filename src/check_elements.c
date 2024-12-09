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

int	check_sym_unit(t_vec3 angle)
{
	if ((angle.x < -1 || angle.x > 1) ||(angle.y < -1 || angle.y > 1) || (angle.z < -1 || angle.z > 1))
	{
		ft_printf("Error\nAngle outside symmetrical unit range.\n");
		return (1);
	}
	return (0);
}

int	check_unit(double ratio)
{
	if ((ratio < 0 || ratio > 1))
	{
		ft_printf("Error\nRatio outside unit range.\n");
		return (1);
	}
	return (0);
}

int	check_colour_range(t_colour rgb)
{
	if ((rgb.red < 0 || rgb.red > 255) || (rgb.green < 0 || rgb.green > 255) || (rgb.blue < 0 || rgb.blue > 255))
	{
		ft_printf("Error\nRBG outside 0-255 range.\n");
		return (1);
	}
	return (0);
}

int	check_positive(double obj_dimensions)
{
	if (obj_dimensions <= 0)
	{
		ft_printf("Error\nObject dimension values not positive.\n");
		return (1);
	}
	return (0);
}

int	check_fov(int fov)
{
	if (fov < 0 || fov > 180)
	{
		ft_printf("Error\nFOV outside range.\n");
		return (1);
	}
	return (0);
}