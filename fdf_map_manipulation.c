//
// Created by Volodymyr DANYLIUK on 2019-02-16.
//

#include "fdf.h"

void 	fdf_move_map(int i, void *mlxv)
{
	int			dx;
	int			dy;
	t_map_lines	*buff;
	t_mlx_ptr	*mlx;

	dx = 0;
	dy = 0;
	mlx = (t_mlx_ptr *)(mlxv);
	i == 123 ? dx = 25 : 0;
	i == 124 ? dx = -25 : 0;
	i == 125 ? dy = -25 : 0;
	i == 126 ? dy = 25 : 0;
	buff = mlx->map_iso;
	while (buff != NULL)
	{
		buff->map_chars->x += dx;
		buff->map_chars->y += dy;
		buff = buff->next;
	}
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	fdf_print_map_mlx_corr(mlx);
}

void	fdf_zoom_map_xy(int i, void *mlxv)
{
	int				zoom;
	t_map_lines		*buff;
	t_mlx_ptr		*mlx;
	static int 		min_zoom = 0;

	zoom = 2;
	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map_iso;
	while (buff != NULL)
	{
		if (i == 30 && min_zoom < 5)
		{
			buff->map_chars->x *= zoom;
			buff->map_chars->y *= zoom;
		}
		if (i == 33 && min_zoom > 0)
		{
			buff->map_chars->x /= zoom;
			buff->map_chars->y /= zoom;
		}
		buff = buff->next;
	}
	if (min_zoom < 5 && i == 30)
		min_zoom++;
	if (min_zoom > 0 && i == 33)
		min_zoom--;
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	fdf_center_map(mlx->map_iso);
	fdf_print_map_mlx_corr(mlx);
}

void	fdf_multiply_z(int i, void *mlxv)
{
	int				zoom;
	t_map_lines		*buff;
	t_mlx_ptr		*mlx;
	static int 		min_zoom = 0;

	zoom = 2;
	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map;
}