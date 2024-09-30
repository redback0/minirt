
#include "minirt.h"
#include <unistd.h>

int main(void)
{
	t_mlx	mlx;

	get_mlx_dat(&mlx);
	mlx_put_image_to_window(mlx.mlxptr, mlx.winptr, mlx.img.img, 0, 0);
	sleep(20);
	cleanup_mlx(&mlx);
}
