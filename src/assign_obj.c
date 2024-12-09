/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:15:28 by nlehmeye          #+#    #+#             */
/*   Updated: 2024/12/03 20:26:54 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	assign_pl(char **elements, t_scene *scene)
{
	t_obj	*plane;
	t_list	*obj;
	int		err;
	
	err = 0;
	plane = malloc(sizeof(*plane));
	if (!plane)
	{
		printf("Error\nPlane Malloc Failed.\n");
		return (1);
	}
	obj = ft_lstnew((void *)plane);
	ft_lstadd_front(&scene->objs, obj);
	ft_bzero(plane, sizeof(*plane));
	if (count_array_rows((void **)elements) != 4)
	{
		printf("Error\nIncorrect number of element pl info.\n");
		return (1);
	}
	plane->id = PLANE;
	err += assign_vector(elements[1], &plane->pos);
	err += assign_vector(elements[2], &plane->angle);
	err += check_sym_unit(plane->angle);
	err += assign_colour(elements[3], &plane->colour);
	return (err);
}

int	assign_sp(char **elements, t_scene *scene)
{
	t_obj	*sphere;
	t_list	*obj;
	int		err;

	err = 0;
	sphere = malloc(sizeof(*sphere));
	if (!sphere)
	{
		printf("Error\nSphere Malloc Failed.\n");
		return (1);
	}
	obj = ft_lstnew((void *)sphere);
	ft_lstadd_front(&scene->objs, obj);
	ft_bzero(sphere, sizeof(*sphere));
	if (count_array_rows((void **)elements) != 4)
	{
		printf("Error\nIncorrect number of element sp info.\n");
		return (1);
	}
	sphere->id = SPHERE;
	err += assign_vector(elements[1], &sphere->pos);
	sphere->diameter = assign_obj_assist(elements[2], &err);
	err += check_positive(sphere->diameter);
	err += assign_colour(elements[3], &sphere->colour);
	return (err);
}
int	assign_cy(char **elements, t_scene *scene)
{
	t_obj	*cylinder;
	t_list	*obj;
	int		err;

	err = 0;
	cylinder = malloc(sizeof(*cylinder));
	if (!cylinder)
	{
		printf("Error\nCylinder Malloc Failed.\n");
		return (1);
	}
	obj = ft_lstnew((void *)cylinder);
	ft_lstadd_front(&scene->objs, obj);
	ft_bzero(cylinder, sizeof(*cylinder));
	if (count_array_rows((void **)elements) != 6)
	{
		printf("Error\nIncorrect number of element cy info\n");
		return (1);
	}
	cylinder->id = CYLINDER;
	cylinder->diameter = assign_obj_assist(elements[3], &err);
	cylinder->height = assign_obj_assist(elements[4], &err);
	assign_cy_assist(elements, cylinder, &err);
	return (err);
}

void	assign_cy_assist(char **elements, t_obj *cylinder, int *err)
{
	*err += assign_vector(elements[1], &cylinder->pos);
	*err += assign_vector(elements[2], &cylinder->angle);
	*err += check_sym_unit(cylinder->angle);
	*err += check_positive(cylinder->diameter);
	*err += check_positive(cylinder->height);
	*err += assign_colour(elements[5], &cylinder->colour);
}

double	assign_obj_assist(char *element, int *err)
{
	int		obj_err;
	double	obj_dimension;

	obj_err = 0;
	obj_dimension = ft_atod_strict(element, &obj_err);
	if (obj_err != 0)
	{
		printf("Error\natod Error in attempt to assign object.\n");
		(*err)++;
	}
	return (obj_dimension);
}