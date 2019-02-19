//
// Created by Volodymyr DANYLIUK on 2019-02-06.
//

#include "fdf.h"

void			fdf_xy_initiation(t_map_lines *map)
{
	t_map_char	*buff;
	t_map_char	*buff_down;
	int 		x;
	int 		y;

	buff = map->map_chars;
	y = 0;
	while (buff != NULL)
	{
		x = 0;
		buff_down = buff->down;
		while (buff != NULL)
		{
			buff->x = x;
			buff->y	= y;
			x = x + 10;
			buff = buff->next;
		}
		buff = buff_down;
		y = y + 10;
	}
}

t_map_lines		*fdf_add_new_info(t_map_lines *buff, t_map_char *info)
{
	t_map_lines		*buff_buff;

	buff_buff = buff;
	if (buff == NULL)
	{
		buff = (t_map_lines*)malloc(sizeof(*buff));
		(buff)->map_chars = info;
		(buff)->prev = NULL;
		(buff)->next = NULL;
		return (buff);
	}
	while((buff)->next != NULL)
		(buff) = (buff)->next;
	(buff)->next = (t_map_lines*)malloc(sizeof(*buff));
	(buff)->next->prev = (buff);
	(buff)->next->map_chars = info;
	(buff)->next->next = NULL;
	(buff)->map_chars->next = (buff)->next->map_chars;
	(buff)->next->map_chars->prev = (buff)->map_chars;
	return (buff_buff);
}

t_map_char		*fdf_info_read(char *str)
{
	char		**argument;
	t_map_char	*info;

	argument = ft_strsplit(str, ',');
	info = (t_map_char*)malloc(sizeof(*info));
	info->z = ft_atoi(*argument);
	info->color = fdf_16to10(*(argument + 1));
	info->next = NULL;
	info->down = NULL;
	info->prev = NULL;
	fdf_free_split(argument);
	return (info);
}

t_map_lines		*fdf_add_end_map(t_map_lines *map, t_map_lines *buff)
{
	t_map_lines		*map_buff_end;
	t_map_lines		*map_buff_syn;

	if (map == NULL)
		return (buff);
	map_buff_end = map;
	map_buff_syn = map;
	while (map_buff_end->next != NULL)
		map_buff_end = map_buff_end->next;
	while (map_buff_syn->map_chars->down != NULL)
		map_buff_syn = map_buff_syn->next;
	map_buff_end->next = buff;
	buff->prev = map_buff_end;
	while (buff != NULL)
	{
		map_buff_syn->map_chars->down = buff->map_chars;
		buff = buff->next;
		map_buff_syn = map_buff_syn->next;
	}
	return (map);
}

t_map_lines		*fdf_create_tmap(const char *str)
{
	t_map_lines		*buff;
	t_map_char		*info;
	char 			**buffstrhead;
	char 			**buffstr;

	buffstrhead = ft_strsplit(str, ' ');
	buffstr = buffstrhead;
	buff = NULL;
	while (*buffstr != 0)
	{
		info = fdf_info_read(*buffstr);
		buff = fdf_add_new_info(buff, info);
		buffstr++;
	}
	fdf_free_split(buffstrhead);
	return (buff);
}

t_map_lines		*fdf_initiation(int *fd, char *param)
{
	char			*line;
	t_map_lines		*map;
	t_map_lines		*buff;

	*fd = open(param, O_RDONLY);
	if (fdf_validator(*fd) == 1)
		fdf_error("Validator = not ok", 9);
	ft_putendl("Validator = ok");
	close(*fd);
	*fd = open(param, O_RDONLY);
	map = NULL;
	while (get_next_line(*fd, &line))
	{
		buff = fdf_create_tmap(line);
		map = fdf_add_end_map(map, buff);
		free(line);
	}
	fdf_xy_initiation(map);
	close(*fd);
	return (map);
}

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
			copy_buff = fdf_add_new_info(copy_buff, fdf_copy_info(buff->map_chars));
			buff = buff->next;
		}
		copy_buff = fdf_add_new_info(copy_buff, fdf_copy_info(buff->map_chars));
		copy_head = fdf_add_end_map(copy_head, copy_buff);
		copy_buff = NULL;
		buff = buff->next;
	}
	return (copy_head);
}