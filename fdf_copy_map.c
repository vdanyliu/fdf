/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_copy_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:26:57 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/02/22 14:33:08 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map_char		*fdf_copy_info(t_map_char *origin)
{
	t_map_char *back;

	back = (t_map_char*)malloc(sizeof(*back));
	back->color = origin->color;
	back->x = origin->x;
	back->y = origin->y;
	back->z = origin->z;
	back->next = NULL;
	back->down = NULL;
	back->prev = NULL;
	return (back);
}

t_map_lines		*fdf_copy_map(t_map_lines *origin)
{
	t_map_lines	*buff;
	t_map_lines *copy_head;
	t_map_lines	*copy_buff;
	t_map_char	*buff_info;

	copy_head = NULL;
	copy_buff = NULL;
	buff = origin;
	while (buff != NULL)
	{
		while (buff->map_chars->next)
		{
			copy_buff = fdf_add_new_info(copy_buff,
					fdf_copy_info(buff->map_chars));
			buff = buff->next;
		}
		copy_buff = fdf_add_new_info(copy_buff, fdf_copy_info(buff->map_chars));
		copy_head = fdf_add_end_map(copy_head, copy_buff);
		copy_buff = NULL;
		buff = buff->next;
	}
	return (copy_head);
}

void			*fdf_copy_map_full_info(t_map_lines *from, t_map_lines *in)
{
	t_map_lines		*frombuff;
	t_map_lines		*inbuff;

	frombuff = from;
	inbuff = in;
	while (frombuff)
	{
		inbuff->map_chars->x = frombuff->map_chars->x;
		inbuff->map_chars->y = frombuff->map_chars->y;
		inbuff->map_chars->z = frombuff->map_chars->z;
		inbuff->map_chars->color = frombuff->map_chars->color;
		inbuff = inbuff->next;
		frombuff = frombuff->next;
	}
}
