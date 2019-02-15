//
// Created by Volodymyr DANYLIUK on 2019-02-06.
//
#include "fdf.h"

static int	fdf_rgb_check(char *str)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (str == NULL)
		return (1);
	if (*str != '0')
		return (0);
	if (*(str + 1) != 'x')
		return (0);
	str = str + 2;
	while(*str)
	{
		if ((*str >= 'A' && *str <= 'F') || (*str >= '0' && *str <= '9'))
			i--;
		str++;
		i++;
		j++;
	}
	if (i != 0 || j != 6)
		return (0);
	return (1);
}

static int	fdf_digit_check(char *str)
{
	if (*str == '-')
		str++;
	if (ft_isdigit(*str))
		return (1);
	return (0);
}

static int 	fdf_symbols_cheker(char *str)
{
	char		**str_split;
	char 		**buff;
	char		**argument;

	str_split = ft_strsplit(str, ' ');
	buff = str_split;
	if (*buff == 0)
		fdf_error("no symbols", 10);
	while (*buff != NULL)
	{
		argument = ft_strsplit(*buff, ',');
		if (*(argument + 1) != 0 && (*(argument + 2) != 0))
			fdf_error("to more ',' xD", 10);
		fdf_digit_check(*argument) == 0 ? fdf_error("no digit", 10) : 0;
		fdf_rgb_check(*(argument + 1)) == 0 ? fdf_error("no RGB", 10) : 0;
		fdf_free_split(argument);
		buff++;
	}
	fdf_free_split(str_split);
	return (0);
}

static int	fdf_argument_count_cheker(char *str)
{
	static int 	i = 0;
	int 		k;
	char 		**str_split;
	char 		**buff;

	str_split = ft_strsplit(str, ' ');
	buff = str_split;
	k = 0;
	if (i == 0)
	{
		while (*buff++ != NULL)
			i++;
		fdf_free_split(str_split);
		if (i == 0 || i == 1)
			return (1);
		return (0);
	}
	else
		while (*buff++ != NULL)
			k++;
	if (k != i)
	{
		fdf_free_split(str_split);
		return (1);
	}
	fdf_free_split(str_split);
	return (0);
}

static int	fdf_valid_line(char *str)
{
	char *buff;

	buff = str;
	fdf_argument_count_cheker(buff) == 1 ? fdf_error("argument count", 10) : 0;
	fdf_symbols_cheker(buff) == 1 ? fdf_error("invalid symbols", 10) : 0;
	return (0);
}

int 	fdf_validator(int fd)
{
	char 	*line;
	char 	*leak;
	size_t 	i;
	size_t 	flag;

	flag = 0;
	while (get_next_line(fd, &line))
	{
		if (fdf_valid_line(line) == -1)
			fdf_error("ivalid_line", -1);
		free(line);
		flag++;
	}
	if (flag == 0)
		return (1);
	return (0);
}