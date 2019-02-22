/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_math_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:08:45 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/02/22 14:09:30 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			fdf_16to10(char *str)
{
	char	*buff;
	int		res;
	int		power;
	int		byte;

	res = 0;
	byte = 0;
	if (str == NULL)
		return (16777215);
	buff = str;
	buff = buff + 2;
	power = ft_strlen(str + 2);
	while (power > 0)
	{
		if (*buff >= '0' && *buff <= '9')
			byte = *buff - 48;
		if (*buff >= 'A' && *buff <= 'F')
			byte = *buff - 55;
		if (*buff >= 'a' && *buff <= 'f')
			byte = *buff - 87;
		res += ((int)pow(16, --power) * byte);
		buff++;
	}
	return (res);
}

int			fdf_digit_check(char *str)
{
	if (*str == '-')
		str++;
	if (ft_isdigit(*str))
		return (1);
	return (0);
}

void		fdf_xy_initiation(t_map_lines *map)
{
	t_map_char	*buff;
	t_map_char	*buff_down;
	int			x;
	int			y;

	buff = map->map_chars;
	y = 0;
	while (buff != NULL)
	{
		x = 0;
		buff_down = buff->down;
		while (buff != NULL)
		{
			buff->x = x;
			buff->y = y;
			x = x + 10;
			buff = buff->next;
		}
		buff = buff_down;
		y = y + 10;
	}
}
