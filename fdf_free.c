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