//
// Created by Volodymyr DANYLIUK on 2019-02-08.
//

#include "fdf.h"

void	fdf_error(char *str, int error_code)
{
	if (str == NULL || error_code == 0)
		exit (-42);
	ft_putendl(str);
	exit(error_code);
}