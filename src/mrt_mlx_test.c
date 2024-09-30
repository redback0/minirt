
#include "minirt.h"
#include <unistd.h>

int window_closed(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlxptr, mlx->img.img);
	if (DESTROY_DISPLAY)
	{
		mlx_destroy_display(mlx->mlxptr);
		free(mlx->mlxptr);
	}
	exit(0);
}

int main(void)
{
	t_mlx	mlx;

	get_mlx_dat(&mlx);
	mlx_put_image_to_window(mlx.mlxptr, mlx.winptr, mlx.img.img, 0, 0);
	mlx_hook(mlx.winptr, 17, 1L << 5, &window_closed, &mlx);
	mlx_loop(mlx.mlxptr);
}
