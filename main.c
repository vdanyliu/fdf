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
	mlx_ptrs->win_ptr = mlx_new_window(mlx_ptrs->mlx_ptr, 2000, 1000, "fdf");
	return (mlx_ptrs);
}

int 		main(int argc, char **argv)
{
	t_mlx_ptr	*mlx_ptrs;
	t_map_lines	*map;
	int 		fd;

	map = fdf_initiation(&fd, argv[1]);
	fdf_debug_print_map(map);
	mlx_ptrs = mlx_ptr_init();
	fdf_mlx_manipulation(&mlx_ptrs);
	fdf_debug_print_map_mlx(mlx_ptrs, map);
	system("leaks -q fdf");
	mlx_loop(mlx_ptrs->mlx_ptr);
	system("leaks -q fdf");
	return (0);
}