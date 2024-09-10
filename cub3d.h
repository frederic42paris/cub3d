/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:23:24 by arguez            #+#    #+#             */
/*   Updated: 2024/09/10 17:31:59 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define SW 640
# define SH 480
# define MAPW 24
# define MAPH 24
# define KEY_W	119
# define KEY_S	115
# define KEY_D	100
# define KEY_A	97
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define TEXTW 64
# define TEXTH 64

typedef struct s_mlx
{
	void	*mlx_p;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*win_ptr;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	move_speed;
	double	rot_speed;
	double	olddir_x;
	double	oldplane_x;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	void	*text_south;
	int		*text_south_addr;
	void	*text_east;
	int		*text_east_addr;
	void	*text_north;
	int		*text_north_addr;
	void	*text_west;
	int		*text_west_addr;
	// int		texNum;
	double	wall_x;
	int 	tex_x;
	double 	step;
	double	tex_pos;
	int		tex_y;
	int		bits_per_pixel_text_south;
	int		line_length_text_south;
	int		endian_text_south;
	int		bits_per_pixel_text_east;
	int		line_length_text_east;
	int		endian_text_east;
	int		bits_per_pixel_text_north;
	int		line_length_text_north;
	int		endian_text_north;
	int		bits_per_pixel_text_west;
	int		line_length_text_west;
	int		endian_text_west;

	float	raydir_x_o;
	float	raydir_y_o;
	float	raydir_x_i;
	float	raydir_y_i;
	int		p;
	float	pos_z;
	float	row_distance;
	float	floorstep_x;
	float	floorstep_y;
	float	floor_x;
	float	floor_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	// int		checkerBoardPattern;
	// int		floorTexture;
	// int		ceilingTexture;

	char			**map_char;
	int				fd;
	int				hasplayer;
	int				ceiling_color;
	int				floor_color;

	// values needed from parsing
	int				**map_int;
	int				map_width;
	int				map_height;
	char			*path_north;
	char			*path_south;
	char			*path_west;
	char			*path_east;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
	char			**textures;
	char			*string_buffer;
	int				count_no;
	int				count_so;
	int				count_ea;
	int				count_we;
	int				count_c;
	int				count_f;
	int				**map_int_one;
	char			player_char;
	
}		t_mlx;


// utils
void	double_free_int(int **tab, t_mlx *mlx);
void	ender(t_mlx *mlx);
size_t	ft_strlen_word(const char *s);
void	display_data(t_mlx *mlx);
void	display_parsing(t_mlx *mlx);
int		has_alpha_num(char *str);
int		is_space(char c);
int		is_not_space(char c);
int 	is_player_character(char c);
int		parse_input(char *string);

// parsing

int		store_data(t_mlx *mlx);
int		is_empty(t_mlx *mlx, char *temp, char *concat);
void	ssl_subrountine(char **string, char **c2, char **temp,
			int *counter);
int		store_textures(t_mlx *mlx);
int		store_map(t_mlx *mlx);
int		store_map_one(t_mlx *mlx);
void	measure_map(t_mlx *mlx);
int		ft_strdup_digit(const char *s, int *j);
char	*ft_strdup_path(const char *s);
void	find_player(t_mlx *mlx);
int 	create_argb(int a, int r, int g, int b);
int		open_file(t_mlx	*mlx, char *string);

// parsing - check errors

int 	check_map_character(t_mlx *mlx);
int 	check_map_players(t_mlx *mlx);
int 	check_map_line(t_mlx *mlx);
int		check_text_id(t_mlx *mlx, char *str);
int		check_text_dup(t_mlx *mlx);
int		check_text_path(char *str);
int		check_text_rgb(char *str);
int		check_map_walls(t_mlx *mlx);
int		check_argument(char *filename, int inputnumber);

// raycasting

void	draw_walls(t_mlx *mlx);
void	calculate_texture(t_mlx *mlx, int x);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	draw_floor_ceiling(t_mlx *mlx);
int		store_images_addr(t_mlx *mlx);
int		store_images(t_mlx *mlx);
void	move_up_down(t_mlx *mlx, int keycode);
void	move_left_right(t_mlx *mlx, int keycode);
void	rotate_right(t_mlx *mlx, int keycode);
void	rotate_left(t_mlx *mlx, int keycode);
void	init_player_direction(t_mlx *mlx);
void	init_speed(t_mlx *mlx);
void	init_minilibx(t_mlx *mlx);
int		raycasting(t_mlx *mlx);

#endif

// long	ft_atoi_ftext_north(const char *string);
