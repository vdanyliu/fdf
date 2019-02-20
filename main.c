#include "fdf.h"

void		fdf_debug_print_map(t_map_lines *map)
{
	t_map_lines	*buff;
	char		*str;

	buff = map;
	while (buff != NULL)
	{
		str = ft_itoa(buff->map_chars->x);
		ft_putstr(str);
		free(str);
		ft_putstr(",");
		str = ft_itoa(buff->map_chars->y);
		ft_putstr(str);
		ft_putstr(",");
		free(str);
		str = ft_itoa(buff->map_chars->z);
		ft_putstr(str);
		free(str);
		ft_putstr(",color=");
		str = ft_itoa(buff->map_chars->color);
		ft_putstr(str);
		free(str);
		write(1, "\t", 1);
		if ((buff->map_chars->next) == NULL)
			write(1, "\n", 1);
		buff = buff->next;
	}
}

int 		key_release(int keycode, void *param)
{
	if (keycode == 53)
	{
		system("leaks -q fdf");
		exit (0);
	}
	if (keycode >= 123 && keycode <= 126)
		fdf_move_map(keycode, param);
	if (keycode == 33 || keycode == 30)
		fdf_zoom_map_xy(keycode, param);
	if (keycode == 31 || keycode == 35)
		fdf_multiply_z(keycode, param);
	if (keycode == 12 || keycode == 13)
		fdf_rotate_zaxis(keycode, param);
	if (keycode == 0 || keycode == 1)
		fdf_rotate_xaxis(keycode, param);
	if (keycode == 6 || keycode == 7)
		fdf_rotate_yaxis(keycode, param);
	return (0);
}

int			closeprog(void *param)
{
	(void)param;
	system("leaks -q fdf");
	exit(0);
	return (0);
}

int 		test(void)
{
	ft_putendl("Click");
	return (0);
}

void		fdf_mlx_manipulation(t_mlx_ptr *mlx)
{
	mlx_key_hook((mlx)->win_ptr, test, (void*) 0);
	mlx_hook((mlx)->win_ptr, 17, 0, closeprog, (void *) 0);
	mlx_hook((mlx)->win_ptr, 2, 0, key_release, (void *)mlx);

}

t_mlx_ptr	*mlx_ptr_init()
{
	t_mlx_ptr	*mlx_ptrs;

	mlx_ptrs = (t_mlx_ptr*)(malloc)(sizeof(*mlx_ptrs));
	mlx_ptrs->mlx_ptr = mlx_init();
	mlx_ptrs->win_ptr = mlx_new_window(mlx_ptrs->mlx_ptr, 2000, 1000, "fdf");
	mlx_ptrs->map = NULL;
	mlx_ptrs->map_iso = NULL;
	mlx_ptrs->map_origin = NULL;
	return (mlx_ptrs);
}

int 		main(int argc, char **argv)
{
	t_mlx_ptr	*mlx;
	int 		fd;

	mlx = mlx_ptr_init();
	mlx->map_origin = fdf_initiation(&fd, argv[1]);
	fdf_debug_print_map(mlx->map_origin);
	mlx->map = fdf_copy_map(mlx->map_origin);
	mlx->map_iso = fdf_copy_map(mlx->map_origin);
	fdf_mlx_manipulation(mlx);
	fdf_print_map_mlx(mlx);
	system("leaks -q fdf");
	mlx_loop(mlx->mlx_ptr);
	system("leaks -q fdf");
	return (0);
}