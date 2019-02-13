//
// Created by Volodymyr DANYLIUK on 2019-02-06.
//

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "mlx.h"

typedef struct 			s_mlx_ptr
{
	void				*mlx_ptr;
	void				*win_ptr;
}						t_mlx_ptr;

typedef struct			s_map_char
{
	int 				z;
	int 				color;
	struct s_map_char	*next;
	struct s_map_char	*down;
	struct s_map_char	*prev;

}						t_map_char;

typedef	struct 			s_map_lines
{
	t_map_char			*map_chars;
	struct s_map_lines	*next;
	struct s_map_lines	*prev;
}						t_map_lines;

t_map_lines				*fdf_initiation(int *fd, char *param);
void					fdf_error(char *str, int error_code);
int 					fdf_validator(int fd);

#endif
