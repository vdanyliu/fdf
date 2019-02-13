//
// Created by Volodymyr DANYLIUK on 2019-02-06.
//

#include "fdf.h"

t_map_lines		*fdf_initiation(int *fd, char *param)
{
	*fd = open(param, O_RDONLY);
	if (fdf_validator(*fd) == 1)
		fdf_error("Validator", 9);
	fdf_error("Validator = ok", 0);
	return (NULL);
}