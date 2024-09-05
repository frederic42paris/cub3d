/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:23:24 by arguez            #+#    #+#             */
/*   Updated: 2024/09/05 13:09:17 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx/mlx.h"
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
}	t_mlx;

#endif
