/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:55:41 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/02/22 14:57:55 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map_lines		*fdf_alloc_map_center(t_map_lines *map)
{
	t_map_char	*buff;
	int			x;
	int			y;

	x = 0;
	y = 0;
	buff = map->map_chars;
	while ((buff = buff->next) != NULL)
		x++;
	buff = map->map_chars;
	while ((buff = buff->down) != NULL)
		y++;
	x /= 2;
	y /= 2;
	buff = map->map_chars;
	while (x > 0 || y > 0)
	{
		x > 0 ? buff = buff->next : 0;
		y > 0 ? buff = buff->down : 0;
		x--;
		y--;
	}
	while (map->map_chars != buff)
		map = map->next;
	return (map);
}

t_map_lines		*fdf_center_map(t_map_lines *map)
{
	t_map_lines	*buff;
	int			x;
	int			y;
	int			xc;
	int			yc;

	buff = map;
	buff = fdf_alloc_map_center(buff);
	xc = 1000 - buff->map_chars->x;
	yc = 500 - buff->map_chars->y;
	buff = map;
	while (buff != NULL)
	{
		buff->map_chars->x += xc;
		buff->map_chars->y += yc;
		buff = buff->next;
	}
	return (map);
}

t_map_lines		*fdf_iso_map(t_map_lines *map)
{
	t_map_lines	*buff;
	int			x;
	int			y;
	int			z;

	buff = map;
	while (buff != NULL)
	{
		x = buff->map_chars->x;
		y = buff->map_chars->y;
		z = buff->map_chars->z;
		buff->map_chars->x = (int)((x - y) * cos(0.523599));
		buff->map_chars->y = (int)((x + y) * sin(0.523599) - z);
		buff = buff->next;
	}
	map = fdf_center_map(map);
	return (map);
}

void			fdf_print_map_mlx(t_mlx_ptr *mlx)
{
	t_map_lines	*buff;

	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	fdf_copy_map_full_info(mlx->map, mlx->map_iso);
	mlx->map_iso = fdf_iso_map(mlx->map_iso);
	buff = mlx->map_iso;
	fdf_zoom_map_xy(0, mlx);
	while (buff != NULL)
	{
		fdf_put_lines(mlx, buff->map_chars);
		buff = buff->next;
	}
}

void			fdf_print_map_mlx_corr(t_mlx_ptr *mlx)
{
	t_map_lines		*map_buff;

	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	map_buff = mlx->map_iso;
	while (map_buff != NULL)
	{
		fdf_put_lines(mlx, map_buff->map_chars);
		map_buff = map_buff->next;
	}
}
