//
// Created by Volodymyr DANYLIUK on 2019-02-14.
//

#include "fdf.h"

int 		fdf_16to10(char *str)
{
	char 	*buff;
	int 	res;
	int 	power;
	int 	byte;

	power = 5;
	res = 0;
	byte = 0;
	if (str == NULL)
		return (16777215);
	buff = str;
	buff = buff + 2;
	while (power >= 0)
	{
		if (*buff >= '0' && *buff <= '9')
			byte = *buff - 48;
		if (*buff >= 'A' && *buff <= 'F')
			byte = *buff - 55;
		res += ((int)pow(16, power--) * byte);
		buff++;
	}
	return (res);
}