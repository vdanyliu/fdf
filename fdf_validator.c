//
// Created by Volodymyr DANYLIUK on 2019-02-06.
//
#include "fdf.h"

static int 	fdf_argument_count(char *str)
{
	char *buff;

	buff = str;
	while (*buff)
	{
		
	}
	return (0);
}

static int	fdf_valid_line(char *str)
{
	char *buff;
	static int i = 0;

	i == 0 ? i = fdf_argument_count(str) : 0;
	buff = str;
	return (0);
}

int 	fdf_validator(int fd)
{
	char	*str;
	char 	*line;
	char 	*leak;
	size_t 	i;

	str = ft_strnew(1);
	while (get_next_line(fd, &line))
	{
		if (fdf_valid_line(line) == -1)
			fdf_error("ivalid_line", -1);
	}
	return (1);
}