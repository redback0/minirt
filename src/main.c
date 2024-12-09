/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:43:37 by nlehmeye          #+#    #+#             */
/*   Updated: 2024/12/09 13:27:09 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	window_closed(t_mrt_dat *dat)
{
	ft_lstclear(&(dat->scene.objs), free);
	cleanup_mlx(&(dat->mlx));
	exit(0);
}

int	main(int argc, char **argv)
{
	t_mrt_dat	dat;
	int			err;

	err = 0;
	ft_bzero(&dat, sizeof(dat));
	(void)argv;
	if (argc != 2)
	{
		printf("Error\nIncorrect Number of Arguments.\n");
		return (1);
	}
	parse_input(argv[1], &dat.scene);
	if (err != 0)
		ft_lstclear(&(dat.scene.objs), free);
	get_mlx_dat(&dat);
	mlx_put_image_to_window(dat.mlx.mlxptr, dat.mlx.winptr, dat.mlx.img.img,
		0, 0);
	mlx_hook(dat.mlx.winptr, 17, 1L << 5, &window_closed, &dat);
	mlx_loop(dat.mlx.mlxptr);
	return (0);
}


// int err;

// err = 0;
// err += firstfunction();
// err += secondfunction();
// err += thirdfunction();

// return (err);

// if (err != 0)
// ft_free()