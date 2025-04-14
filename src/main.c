/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:43:37 by nlehmeye          #+#    #+#             */
/*   Updated: 2025/04/14 12:42:42 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	window_closed(t_mrt_dat *dat)
{
	ft_lstclear(&(dat->scene.objs), free);
	cleanup_mlx(&(dat->mlx));
	exit(0);
}

// here cause no space in mrt_mlx.c
int	key_hook(int key, t_mrt_dat *dat)
{
	//printf("%x\n", key);
	if (key == K_ESCAPE)
	{
		cleanup_mlx(&dat->mlx);
		ft_lstclear(&(dat->scene.objs), free);
		exit(0);
	}
	try_movement(key, dat);
	return (0);
}

int	render_frame(t_mrt_dat* dat)
{
	clock_t	start_time;
	clock_t	end_time;

	start_time = clock();
	init_camera(&dat->scene.cam);
	get_all_pixels(dat, raytrace_pixel);
	mlx_put_image_to_window(dat->mlx.mlxptr, dat->mlx.winptr, dat->mlx.img.img,
		0, 0);
	end_time = clock();
	printf("render took %f seconds\n",
		(double)(end_time - start_time) / CLOCKS_PER_SEC);
	return (0);
}


int	main(int argc, char **argv)
{
	t_mrt_dat	dat;
	int			err;

	err = 0;
	ft_bzero(&dat, sizeof(dat));
	if (argc != 2)
	{
		printf("Error\nIncorrect Number of Arguments.\n");
		exit(1);
	}
	err = parse_input(argv[1], &dat.scene);
	if (err != 0)
	{
		ft_lstclear(&(dat.scene.objs), free);
		exit(1);
	}
	get_mlx_dat(&dat);
	render_frame(&dat);
	mlx_loop(dat.mlx.mlxptr);
	return (0);
}
