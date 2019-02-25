/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_manipulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:10:01 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/02/22 14:11:53 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_zoom_map_xy_zoom(int i, int *min_zoom)
{
	*min_zoom = 2;
	i == 30 ? *min_zoom = 6 : 0;
	i == 33 ? *min_zoom = 1 : 0;
}

void		fdf_move_map(int i, void *mlxv)
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
	fdf_print_map_mlx_corr(mlx);
}

void		fdf_zoom_map_xy(int i, void *mlxv)
{
	t_map_lines		*buff;
	t_mlx_ptr		*mlx;
	static int		min_zoom = 2;

	if (i == 0 || (min_zoom == 1 && i == 33) || (min_zoom == 6 && i == 30))
	{
		fdf_zoom_map_xy_zoom(i, &min_zoom);
		return ;
	}
	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map_iso;
	if (min_zoom >= 1 && i == 33)
		min_zoom--;
	if (min_zoom <= 5 && i == 30)
		min_zoom++;
	while (buff && min_zoom > 0)
	{
		i == 30 ? buff->map_chars->x = (buff->map_chars->x * 2) : 0;
		i == 30 ? buff->map_chars->y = (buff->map_chars->y * 2) : 0;
		i == 33 ? buff->map_chars->x = ceil(buff->map_chars->x / 2) : 0;
		i == 33 ? buff->map_chars->y = ceil(buff->map_chars->y / 2) : 0;
		buff = buff->next;
	}
	mlx->map_iso = fdf_center_map(mlx->map_iso);
	fdf_print_map_mlx_corr(mlx);
}

void		fdf_multiply_z(int i, void *mlxv)
{
	t_map_lines		*buff;
	t_map_lines		*orig;
	t_mlx_ptr		*mlx;
	static int		min_zoom = -101;

	min_zoom = i == 31 ? min_zoom - 1 : min_zoom + 1;
	if (min_zoom >= 7 || min_zoom <= -7)
		min_zoom = i == 31 ? 0 : 1;
	mlx = (t_mlx_ptr *)(mlxv);
	buff = mlx->map;
	orig = mlx->map_origin;
	fdf_copy_map_full_info(orig, buff);
	while (buff != NULL)
	{
		if (orig->map_chars->z != 0)
			buff->map_chars->z = orig->map_chars->z * min_zoom;
		buff = buff->next;
		orig = orig->next;
	}
	fdf_print_map_mlx(mlx);
}

void		fdf_deafult(void *mlxv)
{
	t_mlx_ptr		*mlx;

	mlx = (t_mlx_ptr *)(mlxv);
	fdf_copy_map_full_info(mlx->map_origin, mlx->map);
	fdf_gradient(NULL, NULL, 0, 0);
	fdf_print_map_mlx(mlx);
}
