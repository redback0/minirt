/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:01:41 by njackson          #+#    #+#             */
/*   Updated: 2024/11/28 13:08:05 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_mlx_dat(t_mrt_dat *dat)
{
	dat->mlx.mlxptr = mlx_init();
	if (!dat->mlx.mlxptr)
		return (1);
	dat->mlx.winptr = mlx_new_window(dat->mlx.mlxptr, 800, 600,
			"MiniRT by njackson and nlehmeye");
	if (!dat->mlx.winptr)
		return (1);
	dat->mlx.img.img = 0;
	if (new_image(dat->mlx.mlxptr, &dat->mlx.img, 800, 600))
		return (1); //probably cleanup here as well
	mlx_key_hook(dat->mlx.winptr, key_hook, dat);
	//mlx_hook(dat.mlx.winptr, 17, 1L << 5, &window_closed, &dat);
	return (0);
}

int	key_hook(int key, t_mrt_dat *dat)
{
	if (key == K_ESCAPE)
	{
		cleanup_mlx(&dat->mlx);
		// cleanup_scene(&dat->scene);
		exit(0);
	}
	return (0);
}

int	cleanup_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlxptr, mlx->img.img);
	mlx_destroy_window(mlx->mlxptr, mlx->winptr);
	if (DESTROY_DISPLAY)
	{
		mlx_destroy_display(mlx->mlxptr);
		free(mlx->mlxptr);
	}
	return (0);
}

/*
typedef struct s_image
{
	void	*img;
	uint	*imgdat;
	int		height;
	int		width;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_image;
*/

int	new_image(void *mlxptr, t_image *image, int width, int height)
{
	if (image->img)
		mlx_destroy_image(mlxptr, image->img);
	image->img = 0;
	image->img = mlx_new_image(mlxptr, width, height);
	if (!image->img)
		return (1);
	image->width = width;
	image->height = height;
	image->imgdat = (unsigned int *)mlx_get_data_addr(image->img,
			&image->bits_per_pixel, &image->size_line, &image->endian);
	if (!image->imgdat)
		return (1); // note, this would probably have cleanup
	return (0);
}

void	get_all_pixels(t_mrt_dat *dat,
			t_colour (*pixel_func)(t_mrt_dat *, int, int))
{
	t_colour	color;
	int		pixel;
	int		x;
	int		y;

	y = 0;
	while (y < dat->mlx.img.height)
	{
		x = 0;
		while (x < dat->mlx.img.width)
		{
			color = pixel_func(dat, x, y);
			pixel = color.red << 16;
			pixel += color.green << 8;
			pixel += color.blue;
			dat->mlx.img.imgdat[y * dat->mlx.img.width + x] = pixel;
			++x;
		}
		++y;
	}
}
