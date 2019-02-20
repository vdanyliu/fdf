//
// Created by Volodymyr DANYLIUK on 2019-02-20.
//


#include "fdf.h"


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

void					fdf_change_coor_yaxis(t_map_lines *orig, t_map_lines *buff, double i)
{
	double x;
	double y;
	double z;

	while (buff)
	{
		x = buff->map_chars->x;
		y = buff->map_chars->y;
		z = buff->map_chars->z;
		buff->map_chars->x = x * cos(i) + z * sin(i);
		buff->map_chars->y = y;
		buff->map_chars->z = -x * sin(i) + z * cos(i);
		buff = buff->next;
		orig = orig->next;
	}
}

void					fdf_rotate_yaxis(int i, void *mlxv)
{
	t_map_lines		*buff;
	t_map_lines		*orig;
	t_mlx_ptr		*mlx;
	double 			rad;

	rad = 0.0872665;
	i == 6 ? rad = -rad : 0;
	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map;
	orig = mlx->map_origin;
	fdf_change_coor_yaxis(orig, buff, rad);
	fdf_print_map_mlx(mlx);
}

void					fdf_change_coor_xaxis(t_map_lines *orig, t_map_lines *buff, double i)
{
	double				x;
	double				y;
	double				z;

	while (buff)
	{
		x = buff->map_chars->x;
		y = buff->map_chars->y;
		z = buff->map_chars->z;
		buff->map_chars->x = x;
		buff->map_chars->y = (y * cos(i) + z * sin(i));
		buff->map_chars->z = (-y * sin(i) + z * cos(i));
		buff = buff->next;
		orig = orig->next;
	}
}

void					fdf_rotate_xaxis(int i, void *mlxv)
{
	t_map_lines		*buff;
	t_map_lines		*orig;
	t_mlx_ptr		*mlx;
	double 			rad;

	rad = 0.0872665;
	i == 0 ? rad = -rad : 0;
	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map;
	orig = mlx->map_origin;
	fdf_change_coor_xaxis(orig, buff, rad);
	fdf_print_map_mlx(mlx);
}