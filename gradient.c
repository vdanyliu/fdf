/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:41:31 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/02/25 13:41:34 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int 		(rgb_to_int(int *rgb))
{
	int 	i;

	i = 0;
	i = *rgb;
	i = (i << 8) + *(rgb + 1);
	i = (i << 8) + *(rgb + 2);
	return i;
}

static void		int_to_rgb(int i, int *rgb)
{
	*(rgb) = i / (256 * 256);
	*(rgb + 1) = (i / 256) % 256;
	*(rgb + 2) = i % 256;
}

int			fdf_gradient(t_map_char *map0, t_map_char *map1, int x, int y)
{
	double				dist;
	double				curdist;
	static int			flag = 0;
	int 				rgb0[3];
	int 				rgb1[3];

	if (map0 == NULL && map1 == NULL)
	{
		if (flag == 0)
			flag = 1;
		else
			flag = 0;
		if (x == 0 && y == 0)
			flag = 0;
		return (0);
	}
	if (flag != 0 && map0 != NULL && map1 != NULL)
	{
		int_to_rgb(map0->color, rgb0);
		int_to_rgb(map1->color, rgb1);
		dist = pow(pow(map1->x - map0->x, 2) + pow(map1->y - map0->y, 2), 0.5);
		curdist = pow(pow(map1->x - x, 2) + pow(map1->y - y, 2), 0.5);
		dist = 100 / dist * curdist;
		rgb0[0] = rgb1[0] - (rgb1[0] - rgb0[0]) * (dist / 100);
		rgb0[1] = rgb1[1] - (rgb1[1] - rgb0[1]) * (dist / 100);
		rgb0[2] = rgb1[2] - (rgb1[2] - rgb0[2]) * (dist / 100);
		return (rgb_to_int(rgb0));
	}
	return (map1->color);
}
