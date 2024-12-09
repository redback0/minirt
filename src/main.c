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

void	ft_err(char *err_msg, t_mrt_dat *dat, char *line)
{
	ft_printf("Error:\n%s\n", err_msg);
	ft_free(dat, line);
	exit(1);
}

//FUNCTION THAT FREES EVERYTHING
void	ft_free(t_mrt_dat *dat, char *line)
{
	if (line)
		free(line);
	if (dat->scene.objs)
		ft_lstclear(&(dat->scene.objs), free);
}

int	window_closed(t_mrt_dat *dat)
{
	ft_free(dat, NULL);
	cleanup_mlx(&(dat->mlx));
	exit(0);
}

int	main(int argc, char **argv)
{
	t_mrt_dat	dat;

	ft_bzero(&dat, sizeof(dat));
	(void)argv;
	if (argc != 2)
		ft_err("Incorrect Number of Arguments", &dat, NULL);
	parse_input(argv[1], &dat.scene, &dat);
	get_mlx_dat(&dat);
	mlx_put_image_to_window(dat.mlx.mlxptr, dat.mlx.winptr, dat.mlx.img.img,
		0, 0);
	mlx_hook(dat.mlx.winptr, 17, 1L << 5, &window_closed, &dat);
	mlx_loop(dat.mlx.mlxptr);
	return (0);
}
