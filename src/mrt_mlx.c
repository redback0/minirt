/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:01:41 by njackson          #+#    #+#             */
/*   Updated: 2024/09/30 15:54:10 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_mlx_dat(t_mlx *mlx)
{
	mlx->mlxptr = mlx_init();
	if (!mlx->mlxptr)
		return (1);
	mlx->winptr = mlx_new_window(mlx->mlxptr, 800, 600,
			"MiniRT by njackson and nlehmeye");
	if (!mlx->winptr)
		return (1);
	mlx->img.img = 0;
	if (new_image(mlx->mlxptr, &mlx->img, 800, 600))
		return (1); //probably cleanup here as well
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
	image->imgdat = (uint *)mlx_get_data_addr(image->img,
			&image->bits_per_pixel, &image->size_line, &image->endian);
	if (!image->imgdat)
		return (1); // note, this would probably have cleanup
	return (0);
}
