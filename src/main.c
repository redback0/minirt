/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:43:37 by nlehmeye          #+#    #+#             */
/*   Updated: 2024/11/04 11:43:38 by nlehmeye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_err(char *err_msg, t_mrt_dat *dat)
{
	ft_printf("Error:\n%s\n", err_msg);
	//call ft_free, pass through *dat
	(void)dat;
	exit (1);
}

//FUNCTION THAT FREES EVERYTHING
//void	ft_free

int	main(int argc, char **argv)
{
	t_mrt_dat	dat;
	ft_bzero(&dat, sizeof(dat));
	(void)argv;
	if (argc != 2)
		ft_err("Incorrect Number of Arguments", &dat);
	parse_input(argv[1], &dat.scene, &dat);
	
	t_list *holder = dat.scene.objs;
	while (holder != NULL)
	{
		printf("OBJ TYPE: %d\n\n", ((t_obj *)holder->content)->id);
		holder = holder->next;
	}
	return (0);
}
