//
// Created by Volodymyr DANYLIUK on 2019-02-06.
//

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "mlx.h"
# include <math.h>

typedef struct			s_map_char
{
	double				z;
	double				x;
	double					y;
	int					color;
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

typedef struct 			s_mlx_ptr
{
	void				*mlx_ptr;
	void				*win_ptr;
	struct s_map_lines	*map;
	struct s_map_lines	*map_origin;
	struct s_map_lines	*map_iso;
}						t_mlx_ptr;

t_map_lines				*fdf_initiation(int *fd, char *param);
void					fdf_error(char *str, int error_code);
int 					fdf_validator(int fd);
void					fdf_free_split(char **str);
int						fdf_16to10(char *str);
void					fdf_print_map_mlx(t_mlx_ptr *mlx);
void					fdf_print_map_mlx_corr(t_mlx_ptr *mlx);
void					fdf_move_map(int i, void *mlx);
void					fdf_zoom_map_xy(int i, void *mlx);
void					fdf_rotate_zaxis(int i, void *mlx);
void					fdf_rotate_xaxis(int i, void *mlx);
void					fdf_rotate_yaxis(int i, void *mlx);
t_map_lines				*fdf_center_map(t_map_lines *map);
void					fdf_multiply_z(int i, void *mlxv);
void					fdf_free(t_map_lines *leak);
t_map_lines				*fdf_iso_map(t_map_lines *map);
t_map_lines				*fdf_copy_map(t_map_lines *origin);
t_map_lines				*fdf_add_new_info(t_map_lines *buff, t_map_char *info);
t_map_lines				*fdf_add_end_map(t_map_lines *map, t_map_lines *buff);
void					fdf_copy_map_full_info(t_map_lines *from, t_map_lines *in);
void					fdf_deafult(void *mlxv);
void					fdf_put_lines(t_mlx_ptr *mlx, t_map_char *map);
int						fdf_digit_check(char *str);
void					fdf_xy_initiation(t_map_lines *map);
int 					fdf_gradient(t_map_char *map0, t_map_char *map1, int x, int y);
void					fdf_gradient_reprint(void *mlxv);

#endif
