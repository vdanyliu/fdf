#include "fdf.h"

int 		key_release(int keycode, void *param)
{
	(void)param;
	if (keycode == 53)
	{
		exit (0);
	}
	return (0);
}

int			closeprog(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int 		test(void)
{
	ft_putendl("Click");
	return (0);
}

void		fdf_mlx_manipulation(t_mlx_ptr **mlx_ptrs)
{
	mlx_key_hook((*mlx_ptrs)->win_ptr, test, (void*) 0);
	mlx_hook((*mlx_ptrs)->win_ptr, 17, 0, closeprog, (void *) 0);
	mlx_hook((*mlx_ptrs)->win_ptr, 2, 0, key_release, (void *) 0);
}

t_mlx_ptr	*mlx_ptr_init()
{
	t_mlx_ptr	*mlx_ptrs;

	mlx_ptrs = (t_mlx_ptr*)(malloc)(sizeof(*mlx_ptrs));
	mlx_ptrs->mlx_ptr = mlx_init();
	mlx_ptrs->win_ptr = mlx_new_window(mlx_ptrs->mlx_ptr, 500, 500, "fdf");
	return (mlx_ptrs);
}

int 		main(int argc, char **argv)
{
	t_mlx_ptr	*mlx_ptrs;
	t_map_lines	*map;
	int 		fd;

	map = fdf_initiation(&fd, argv[1]);
	mlx_ptrs = mlx_ptr_init();
	fdf_mlx_manipulation(&mlx_ptrs);
	mlx_loop(mlx_ptrs->mlx_ptr);
	return (0);
}