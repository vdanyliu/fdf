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
	t_map_lines		*buff;
	t_map_lines		*orig;
	t_mlx_ptr		*mlx;
	static int 		min_zoom = 1;

	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map;
	orig = mlx->map_origin;
	if (min_zoom >= 2 && i == 33)
		min_zoom--;
	if (min_zoom <= 30 && i == 30)
		min_zoom++;
	while (buff && min_zoom > 0)
	{
		buff->map_chars->x = orig->map_chars->x * min_zoom;
		buff->map_chars->y = orig->map_chars->y * min_zoom;
		buff = buff->next;
		orig = orig->next;
	}
	fdf_print_map_mlx(mlx);
}

void	fdf_multiply_z(int i, void *mlxv)
{
	t_map_lines		*buff;
	t_map_lines		*orig;
	t_mlx_ptr		*mlx;
	static int 		min_zoom = 0;

	if (i == 31)
		min_zoom--;
	if (i == 35)
		min_zoom++;
	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map;
	orig = mlx->map_origin;
	while (buff != NULL)
	{
		if (orig->map_chars->z != 0)
			buff->map_chars->z = orig->map_chars->z * min_zoom;
		buff = buff->next;
		orig = orig->next;
	}
	fdf_print_map_mlx(mlx);
}

void					fdf_change_coor_zaxis(t_map_lines *orig, t_map_lines *buff, double i)
{
	double				x;
	double				y;

	while (buff)
	{
		x = buff->map_chars->x;
		y = buff->map_chars->y;
		buff->map_chars->x = (x * cos(i) - y * sin(i));
		buff->map_chars->y = (y * cos(i) + x * sin(i));
		buff = buff->next;
		orig = orig->next;
	}
}

void					fdf_rotate_zaxis(int i, void *mlxv)
{
	t_map_lines		*buff;
	t_map_lines		*orig;
	t_mlx_ptr		*mlx;
	double 			rad;

	rad = 0.0872665;
	i == 12 ? rad = -rad : 0;
	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map;
	orig = mlx->map_origin;
	fdf_change_coor_zaxis(orig, buff, rad);
	fdf_print_map_mlx(mlx);
}