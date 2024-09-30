
#include "minirt.h"
#include <stdio.h>

t_color	get_color(t_mrt_dat *dat, int x, int y)
{
	t_color	color;
	double	scale;

	(void)y;
	scale = 255.0 / dat->mlx.img.width;
	color.red = 255 - x * scale;
	color.green = x * scale;
	color.blue = 0;
	if (color.red > 255 || color.red < 0)
		printf("RED INCORRECT\n");
	if (color.green > 255 || color.green < 0)
		printf("RED INCORRECT\n");
	return (color);
}

int window_closed(t_mrt_dat *dat)
{
	mlx_destroy_image(dat->mlx.mlxptr, dat->mlx.img.img);
	mlx_destroy_window(dat->mlx.mlxptr, dat->mlx.winptr);
	if (DESTROY_DISPLAY)
	{
		mlx_destroy_display(dat->mlx.mlxptr);
		free(dat->mlx.mlxptr);
	}
	exit(0);
}

int main(void)
{
	t_mrt_dat	dat;

	get_mlx_dat(&dat.mlx);
	get_all_pixels(&dat, *get_color);
	mlx_put_image_to_window(dat.mlx.mlxptr, dat.mlx.winptr, dat.mlx.img.img,
		0, 0);
	mlx_hook(dat.mlx.winptr, 17, 1L << 5, &window_closed, &dat);
	mlx_loop(dat.mlx.mlxptr);
}
