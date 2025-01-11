/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:40:46 by njackson          #+#    #+#             */
/*   Updated: 2025/01/11 16:54:58 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	assign_vector(char *elementinfo, t_vec3 *vector)
{
	char	**xyz;
	int		static_err;

	static_err = 0;
	xyz = ft_split(elementinfo, ',');
	if (count_array_rows((void **)xyz) != 3)
	{
		printf("Error\nIncorrect vector format.\n");
		ft_split_free(xyz, free);
		return (1);
	}
	vector->x = ft_atod_strict(xyz[0], &static_err);
	vector->y = ft_atod_strict(xyz[1], &static_err);
	vector->z = ft_atod_strict(xyz[2], &static_err);
	ft_split_free(xyz, free);
	if (static_err != 0)
	{
		printf("Error\natod Error in attempt to assign vector.\n");
		return (1);
	}
	return (0);
}

int	assign_colour(char *elementinfo, t_colour *rgb)
{
	char	**colour_info;
	int		static_err;

	static_err = 0;
	colour_info = ft_split(elementinfo, ',');
	if (count_array_rows((void **)colour_info) != 3)
	{
		printf("Error\nIncorrect colour format.\n");
		ft_split_free(colour_info, free);
		return (1);
	}
	rgb->red = ft_atoi_strict(colour_info[0], &static_err);
	rgb->green = ft_atoi_strict(colour_info[1], &static_err);
	rgb->blue = ft_atoi_strict(colour_info[2], &static_err);
	static_err += check_colour_range(*rgb);
	ft_split_free(colour_info, free);
	if (static_err != 0)
	{
		printf("Error\natoi Error in attempt to assign colour.\n");
		return (1);
	}
	return (0);
}

int	check_angle(t_angle *angle)
{
	double	self_dot;

	self_dot = vec3_dot(*angle, *angle);
	if (self_dot != 1)
	{
		printf("Error\nNone normalised angle:\n");
		printf("Current value:\n");
		printf("(%f, %f, %f)\n", angle->x, angle->y, angle->z);
		*angle = vec3_mult(*angle, 1 / sqrt(self_dot));
		printf("Should be:\n");
		printf("(%f, %f, %f)\n", angle->x, angle->y, angle->z);
		// return (1); // uncomment for final version
	}
	return (0);
}
