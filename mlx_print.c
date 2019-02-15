//
// Created by Volodymyr DANYLIUK on 2019-02-15.
//

#include "fdf.h"

void			fdf_put_line(t_mlx_ptr *mlx, t_map_char *map0, t_map_char *map1)
{
	int		dx[2];
	int		dy[2];
	int		d[2];
	int		y;
	int		x;

	dx[0] = abs(map1->x - map0->x);
	dy[0] = abs(map1->y - map0->y);
	dx[1] = -1;
	if (map0->x < map1->x)
		dx[1] = 1;
	dy[1] = -1;
	if (map0->y < map1->y)
		dy[1] = 1;
	d[0] = 0 - dy[0] / 2;
	if (dx[0] > dy[0])
		d[0] = dx[0] / 2;
	x = map0->x;
	y = map0->y;
	while (42)
	{
		mlx_pixel_put(mlx->win_ptr, mlx->win_ptr, x, y, map0->color);
		if (x == map1->x && y == map1->y)
			break;
		d[1] = d[0];
		if (d[1] > -dx[0])
		{
			d[0] -= dy[0];
			x += dx[1];
		}
		if (d[1] < dy[0])
		{
			d[0] += dx[0];
			y += dy[1];
		}
	}
}

void			fdf_put_lines(t_mlx_ptr *mlx, t_map_char *map)
{
	if (map->next != NULL)
		fdf_put_line(mlx, map, map->next);
	if (map->down != NULL)
		fdf_put_line(mlx, map, map->down);
}

t_map_lines		*fdf_alloc_map_center(t_map_lines *map)
{
	t_map_char	*buff;
	int 		x;
	int 		y;

	x = 0;
	y = 0;
	buff = map->map_chars;
	while (buff != NULL)
	{
		x++;
		buff = buff->next;
	}
	buff = map->map_chars;
	while (buff != NULL)
	{
		y++;
		buff = buff->down;
	}
	x /= 2;
	y /= 2;
	buff = map->map_chars;
	while (x > 0 && y > 0)
	{
		if (x != 0)
			buff = buff->next;
		if (y != 0)
			buff = buff->down;
		x--;
		y--;
	}
	while (map->map_chars != buff)
		map = map->next;
	return (map);
}

t_map_lines		*fdf_center_map(t_map_lines *map)
{
	t_map_lines *buff;
	int 		x;
	int 		y;
	int 		xc;
	int 		yc;

	buff = map;
	buff = fdf_alloc_map_center(buff);
	xc = 1500 / 2 - buff->map_chars->x / 2;
	yc = 600 / 2 - buff->map_chars->y / 2;
	buff = map;
	while (buff != NULL)
	{
		buff->map_chars->x += xc;
		buff->map_chars->y += yc;
		buff = buff->next;
	}
	return (map);
}

t_map_lines		*fdf_zoom_map(t_map_lines *map)
{
	t_map_lines	*buff;
	t_map_lines	*buff_last;

	buff_last = map;
	while (buff_last->next != NULL)
		buff_last = buff_last->next;
	while (buff_last->map_chars->x < 400 && buff_last->map_chars->y < 400)
	{
		buff = map;
		while (buff != NULL)
		{
			buff->map_chars->x *= 2;
			buff->map_chars->y *= 2;
			buff->map_chars->z *= 1.8;
			buff = buff->next;
		}
	}
	return (map);
}

t_map_lines		*fdf_iso_map(t_map_lines *map)
{
	t_map_lines	*buff;
	int 		x;
	int 		y;
	int 		z;

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
	return (map);
}

void			fdf_debug_print_map_mlx(t_mlx_ptr *mlx, t_map_lines *map)
{
	t_map_lines		*buff;
	t_map_lines		*buff_big;

	map = fdf_zoom_map(map);
	map = fdf_iso_map(map);
	map = fdf_center_map(map);
	buff_big = map;
	while (buff_big != NULL)
	{
		fdf_put_lines(mlx, buff_big->map_chars);
		buff_big = buff_big->next;
	}
}