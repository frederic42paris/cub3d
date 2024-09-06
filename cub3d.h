/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:23:24 by arguez            #+#    #+#             */
/*   Updated: 2024/09/06 16:47:32 by ftanon           ###   ########.fr       */
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
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldTime;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	double	moveSpeed;
	double	rotSpeed;
	double	oldDirX;
	double	oldPlaneX;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;

	void	*greystone;
	int		*greystone_addr;
	void	*bluestone;
	int		*bluestone_addr;
	void	*red;
	int		*red_addr;
	void	*wood;
	int		*wood_addr;
	int		texNum;
	double	wallX;
	int 	texX;
	double 	step;
	double	texPos;
	int		texY;
	int		bits_per_pixel_grey;
	int		line_length_grey;
	int		endian_grey;
	int		bits_per_pixel_blue;
	int		line_length_blue;
	int		endian_blue;
	int		bits_per_pixel_red;
	int		line_length_red;
	int		endian_red;
	int		bits_per_pixel_wood;
	int		line_length_wood;
	int		endian_wood;

	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	int		p;
	float	posZ;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int		tx;
	int		ty;
	int		checkerBoardPattern;
	int		floorTexture;
	int		ceilingTexture;

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
	
}		t_mlx;

int		check_argument(char *filename, int inputnumber);
void	error_message(int num);
int		open_file(t_mlx	*mlx, char *string);
void	display_parsing(t_mlx *mlx);
int		has_alpha_num(char *str);
int		is_space(char c);
int		is_not_space(char c);

void	find_player(t_mlx *mlx, int i, int j);
void	measure_map(t_mlx *mlx, int i, int j);
void	analyse_map(t_mlx *mlx);
void	copymap(t_mlx *mlx);

size_t	ft_strlen_word(const char *s);
int 	create_argb(int a, int r, int g, int b);
int		ft_strdup_digit(const char *s, int *j);
char	*ft_strdup_path(const char *s);
int		is_identifier(t_mlx *mlx, char *str);
int		parse_information(t_mlx *mlx, char *str);
void	parse_elements(t_mlx *mlx);
int		is_empty(t_mlx *mlx, char *temp, char *concat);
int		parse_map(t_mlx *mlx);

int		args_checker(int argc, char *filename);
int		**parser(char *filename, t_mlx *mlx);
void	array_incrementer(char *line, int **textures);
int		count_lines(char *filename);
void	count_texture_tags(char **map, int **textures);
char	*get_tag(char *line);
int		test_access(char **map, char *tag);
int		get_map_size(char **map, t_mlx *mlx);

void	init_minilibx(t_mlx *mlx);
void	init_values(t_mlx *mlx);
int		raycasting(t_mlx *mlx);
#endif
