//
// Created by Volodymyr DANYLIUK on 2019-02-08.
//

#include "fdf.h"

void	fdf_error(char *str, int error_code)
{
	system("leaks -q fdf");
	ft_putendl(str);
	exit(error_code);
}