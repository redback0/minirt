
#include "minirt.h"
#include <unistd.h>

int main(void)
{
	t_mlx	mlx;

	get_mlx_dat(&mlx);
	sleep(5);
	cleanup_mlx(&mlx);
}
