/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_manipulation2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:40:07 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/02/22 14:55:18 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fdf_change_coor(int j, t_map_lines *orig,
		t_map_lines *buff, double i)
{
	double x;
	double y;
	double z;

	while (buff)
	{
		x = buff->map_chars->x;
		y = buff->map_chars->y;
		z = buff->map_chars->z;
		j == 6 ? buff->map_chars->x = x * cos(i) + z * sin(i) : 0;
		j == 6 ? buff->map_chars->z = -x * sin(i) + z * cos(i) : 0;
		j == 12 ? buff->map_chars->x = (x * cos(i) - y * sin(i)) : 0;
		j == 12 ? buff->map_chars->y = (y * cos(i) + x * sin(i)) : 0;
		j == 0 ? buff->map_chars->y = (y * cos(i) + z * sin(i)) : 0;
		j == 0 ? buff->map_chars->z = (-y * sin(i) + z * cos(i)) : 0;
		buff = buff->next;
		orig = orig->next;
	}
}

void			fdf_rotate_zaxis(int i, void *mlxv)
{
	t_map_lines		*buff;
	t_map_lines		*orig;
	t_mlx_ptr		*mlx;
	double			rad;

	rad = 0.0872665;
	i == 12 ? rad = -rad : 0;
	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map;
	orig = mlx->map_origin;
	fdf_change_coor(12, orig, buff, rad);
	fdf_print_map_mlx(mlx);
}

void			fdf_rotate_yaxis(int i, void *mlxv)
{
	t_map_lines		*buff;
	t_map_lines		*orig;
	t_mlx_ptr		*mlx;
	double			rad;

	rad = 0.0872665;
	i == 6 ? rad = -rad : 0;
	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map;
	orig = mlx->map_origin;
	fdf_change_coor(6, orig, buff, rad);
	fdf_print_map_mlx(mlx);
}

void			fdf_rotate_xaxis(int i, void *mlxv)
{
	t_map_lines		*buff;
	t_map_lines		*orig;
	t_mlx_ptr		*mlx;
	double			rad;

	rad = 0.0872665;
	i == 0 ? rad = -rad : 0;
	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map;
	orig = mlx->map_origin;
	fdf_change_coor(0, orig, buff, rad);
	fdf_print_map_mlx(mlx);
}

void			fdf_gradient_reprint(void *mlxv)
{
	t_mlx_ptr	*mlx;

	mlx = (t_mlx_ptr *)(mlxv);
	fdf_gradient(NULL, NULL, 1, 1);
	fdf_print_map_mlx_corr(mlx);
}
