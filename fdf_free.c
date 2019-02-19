//
// Created by Volodymyr DANYLIUK on 2019-02-13.
//

#include "fdf.h"

void	fdf_free_split(char **str)
{
	char **buff;
	buff = str;
	while (*str)
	{
		free(*str);
		str++;
	}
	free(buff);
}

void	fdf_free(t_map_lines *leak)
{
	while (leak->next != NULL)
	{
		leak = leak->next;
		free(leak->prev->map_chars);
		free(leak->prev);
	}
	free(leak->map_chars);
	free(leak);
}