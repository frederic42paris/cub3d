/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/05 18:04:40 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(mlx->mlx_p, mlx->win_ptr);
		exit(0);
	}
	if (keycode == KEY_W)
	{
		if (!mlx->map_int[(int)(mlx->posX + mlx->dirX * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX += mlx->dirX * mlx->moveSpeed;
		if (!mlx->map_int[(int)mlx->posX][(int)(mlx->posY + mlx->dirY * mlx->moveSpeed)])
			mlx->posY += mlx->dirY * mlx->moveSpeed;
	}
	if (keycode == KEY_S)
	{
		if (!mlx->map_int[(int)(mlx->posX - mlx->dirX * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX -= mlx->dirX * mlx->moveSpeed;
		if (!mlx->map_int[(int)mlx->posX][(int)(mlx->posY - mlx->dirY * mlx->moveSpeed)])
			mlx->posY -= mlx->dirY * mlx->moveSpeed;
	}
	if (keycode == KEY_D)
	{
		if (!mlx->map_int[(int)(mlx->posX + mlx->dirY * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX += mlx->dirY * mlx->moveSpeed;
		if (!mlx->map_int[(int)mlx->posX][(int)(mlx->posY - mlx->dirX * mlx->moveSpeed)])
			mlx->posY -= mlx->dirX * mlx->moveSpeed;
	}
	if (keycode == KEY_A)
	{
		if (!mlx->map_int[(int)(mlx->posX + mlx->dirY * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX -= mlx->dirY * mlx->moveSpeed;
		if (!mlx->map_int[(int)mlx->posX][(int)(mlx->posY + mlx->dirX * mlx->moveSpeed)])
			mlx->posY += mlx->dirX * mlx->moveSpeed;
	}
	if (keycode == KEY_LEFT)
	{
		mlx->oldDirX = mlx->dirX;
		mlx->dirX = mlx->dirX * cos(mlx->rotSpeed) - mlx->dirY * sin(mlx->rotSpeed);
		mlx->dirY = mlx->oldDirX * sin(mlx->rotSpeed) + mlx->dirY * cos(mlx->rotSpeed);
		mlx->oldPlaneX = mlx->planeX;
		mlx->planeX = mlx->planeX * cos(mlx->rotSpeed) - mlx->planeY * sin(mlx->rotSpeed);
		mlx->planeY = mlx->oldPlaneX * sin(mlx->rotSpeed) + mlx->planeY * cos(mlx->rotSpeed);
	}
	if (keycode == KEY_RIGHT)
	{
		mlx->oldDirX = mlx->dirX;
		mlx->dirX = mlx->dirX * cos(-mlx->rotSpeed) - mlx->dirY * sin(-mlx->rotSpeed);
		mlx->dirY = mlx->oldDirX * sin(-mlx->rotSpeed) + mlx->dirY * cos(-mlx->rotSpeed);
		mlx->oldPlaneX = mlx->planeX;
		mlx->planeX = mlx->planeX * cos(-mlx->rotSpeed) - mlx->planeY * sin(-mlx->rotSpeed);
		mlx->planeY = mlx->oldPlaneX * sin(-mlx->rotSpeed) + mlx->planeY * cos(-mlx->rotSpeed);
	}
	mlx_destroy_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, SW, SH);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	return (0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void floor_ceiling(t_mlx *mlx)
{
	int	x;
	int y;

	y = SH / 2 + 1;
	
	while (y < SH)
	{
		mlx->rayDirX0 = mlx->dirX - mlx->planeX;
		mlx->rayDirY0 = mlx->dirY - mlx->planeY;
		mlx->rayDirX1 = mlx->dirX + mlx->planeX;
		mlx->rayDirY1 = mlx->dirY + mlx->planeY;

		mlx->p = y - SH / 2;

		mlx->posZ = 0.5 * SH;
		mlx->rowDistance = mlx->posZ / mlx->p;

		mlx->floorStepX = mlx->rowDistance * (mlx->rayDirX1 - mlx->rayDirX0) / SW;
		mlx->floorStepY = mlx->rowDistance * (mlx->rayDirY1 - mlx->rayDirY0) / SW;

		mlx->floorX = mlx->posX + mlx->rowDistance * mlx->rayDirX0;
		mlx->floorY = mlx->posY + mlx->rowDistance * mlx->rayDirY0;

		x = 0;
		while (x < SW)
		{
			mlx->cellX = (int)(mlx->floorX);
			mlx->cellY = (int)(mlx->floorY);
			mlx->tx = (int)(TEXTW * (mlx->floorX - mlx->cellX)) & (TEXTW - 1);
			mlx->ty = (int)(TEXTH * (mlx->floorY - mlx->cellY)) & (TEXTH - 1);

			mlx->floorX += mlx->floorStepX;
			mlx->floorY += mlx->floorStepY;


			mlx->color = mlx->floor_color;

			my_mlx_pixel_put(mlx, x, y, mlx->color);
			mlx->color = mlx->ceiling_color;

			my_mlx_pixel_put(mlx, x, SH - y - 1, mlx->color);

			x++;
		}

		y++;
	}
}

void walls(t_mlx *mlx)
{
	int	x;
	int y;

	x = 0;
	while (x < SW)
	{
		//calculate ray position and direction
		mlx->cameraX = 2 * x / (double)SW - 1;
		mlx->rayDirX = mlx->dirX + mlx->planeX * mlx->cameraX;
		mlx->rayDirY = mlx->dirY + mlx->planeY * mlx->cameraX;

		//which box of the map we're in
		mlx->mapX = (int)mlx->posX;
		mlx->mapY = (int)mlx->posY;

		//length of ray from one x or y-side to next x or y-side
		mlx->deltaDistX = fabs(1 / mlx->rayDirX);
		mlx->deltaDistY = fabs(1 / mlx->rayDirY);

		mlx->hit = 0;

		//calculate step and initial sideDist
		if (mlx->rayDirX < 0)
		{
			mlx->stepX = -1;
			mlx->sideDistX = (mlx->posX - mlx->mapX) * mlx->deltaDistX;
		}
		else
		{
			mlx->stepX = 1;
			mlx->sideDistX = (mlx->mapX + 1.0 - mlx->posX) * mlx->deltaDistX;
		}
		if (mlx->rayDirY < 0)
		{
			mlx->stepY = -1;
			mlx->sideDistY = (mlx->posY - mlx->mapY) * mlx->deltaDistY;
		}
		else
		{
			mlx->stepY = 1;
			mlx->sideDistY = (mlx->mapY + 1.0 - mlx->posY) * mlx->deltaDistY;
		}

		//perform DDA
		while (mlx->hit == 0)
		{
			if (mlx->sideDistX < mlx->sideDistY)
			{
				mlx->sideDistX += mlx->deltaDistX;
				mlx->mapX += mlx->stepX;
				mlx->side = 0;
			}
			else
			{
				mlx->sideDistY += mlx->deltaDistY;
				mlx->mapY += mlx->stepY;
				mlx->side = 1;
			}
			if (mlx->map_int[mlx->mapX][mlx->mapY] > 0)
				mlx->hit = 1;
		}

		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (mlx->side == 0)
			mlx->perpWallDist = (mlx->sideDistX - mlx->deltaDistX);
		else
			mlx->perpWallDist = (mlx->sideDistY - mlx->deltaDistY);

		//Calculate height of line to draw on screen
		mlx->lineHeight = (int)(SH / mlx->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		mlx->drawStart = -mlx->lineHeight / 2 + SH / 2;
		if (mlx->drawStart < 0)
			mlx->drawStart = 0;
		mlx->drawEnd = mlx->lineHeight / 2 + SH / 2;
		if (mlx->drawEnd >= SH)
			mlx->drawEnd = SH - 1;

		//texturing calculations
		mlx->texNum = mlx->map_int[mlx->mapX][mlx->mapY] - 1;
		
		//calculate value of wallX
		if(mlx->side == 0)
			mlx->wallX = mlx->posY + mlx->perpWallDist * mlx->rayDirY;
		else
			mlx->wallX = mlx->posX + mlx->perpWallDist * mlx->rayDirX;
		mlx->wallX -= floor((mlx->wallX));
		
		//x coordinate on the texture
		mlx->texX = (int)(mlx->wallX * (double)(TEXTW));
		if(mlx->side == 0 && mlx->rayDirX > 0)
			mlx->texX = TEXTW - mlx->texX - 1;
		if(mlx->side == 1 && mlx->rayDirY < 0)
			mlx->texX = TEXTW - mlx->texX - 1;

		// How much to increase the texture coordinate per screen pixel
		mlx->step = 1.0 * TEXTH / mlx->lineHeight;

		// Starting texture coordinate
		mlx->texPos = (mlx->drawStart - SH / 2 + mlx->lineHeight / 2) * mlx->step;

		y = mlx->drawStart;
		while (y < mlx->drawEnd)
		{
			mlx->texY = (int)mlx->texPos & (TEXTH - 1);
        	mlx->texPos += mlx->step;

			if (mlx->side == 0 && mlx->rayDirX < 0)
				mlx->color = mlx->bluestone_addr[mlx->texY * TEXTH + mlx->texX];
			else if (mlx->side == 0 && mlx->rayDirX >= 0)
				mlx->color = mlx->greystone_addr[mlx->texY * TEXTH + mlx->texX];
			else if (mlx->side == 1 && mlx->rayDirY < 0)
				mlx->color = mlx->red_addr[mlx->texY * TEXTH + mlx->texX];
			else if (mlx->side == 1 && mlx->rayDirY >= 0)
				mlx->color = mlx->wood_addr[mlx->texY * TEXTH + mlx->texX];
			// int d = y * 256 - SH * 128 + mlx->lineHeight * 128;
			// mlx->texY = ((d * TEXTH) / mlx->lineHeight) / 256;
			// mlx->color = mlx->greystone_addr[mlx->texY * TEXTW + mlx->texX];
			
			my_mlx_pixel_put(mlx, x, y, mlx->color);
			y++;
		}
		x++;
	}
}

int	raycasting(t_mlx *mlx)
{
	floor_ceiling(mlx);
	walls(mlx);
	mlx_put_image_to_window(mlx->mlx_p, mlx->win_ptr, mlx->img, 0, 0);
	return 0;
}

void	init_values(t_mlx *mlx)
{
	// mlx->posX = 22;
	// mlx->posY = 12;
	mlx->dirX = -1;
	mlx->dirY = 0;
	mlx->planeX = 0;
	mlx->planeY = 0.66;
	mlx->time = 0;
	mlx->oldTime = 0;
	mlx->moveSpeed = 1;
	mlx->rotSpeed = 0.5;
}

int	store_images(t_mlx *mlx)
{
	int		img_width;
	int		img_height;

	mlx->greystone = mlx_xpm_file_to_image(mlx->mlx_p, mlx->path_north, &img_width, &img_height);
	mlx->bluestone = mlx_xpm_file_to_image(mlx->mlx_p, mlx->path_south, &img_width, &img_height);
	mlx->red = mlx_xpm_file_to_image(mlx->mlx_p, mlx->path_east, &img_width, &img_height);
	mlx->wood = mlx_xpm_file_to_image(mlx->mlx_p, mlx->path_west, &img_width, &img_height);
	return (0);
}

int	store_images_addr(t_mlx *mlx)
{
	mlx->greystone_addr = (int *)mlx_get_data_addr(mlx->greystone, &mlx->bits_per_pixel_grey, &mlx->line_length_grey, &mlx->endian_grey);
	mlx->bluestone_addr = (int *)mlx_get_data_addr(mlx->bluestone, &mlx->bits_per_pixel_blue, &mlx->line_length_blue, &mlx->endian_blue);
	mlx->red_addr = (int *)mlx_get_data_addr(mlx->red, &mlx->bits_per_pixel_red, &mlx->line_length_red, &mlx->endian_red);
	mlx->wood_addr = (int *)mlx_get_data_addr(mlx->wood, &mlx->bits_per_pixel_wood, &mlx->line_length_wood, &mlx->endian_wood);
	return (0);
}

void	init_minilibx(t_mlx *mlx)
{
	mlx->mlx_p = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_p, SW, SH, "cub3d");
	mlx->img = mlx_new_image(mlx->mlx_p, SW, SH);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	store_images(mlx);
	store_images_addr(mlx);
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask, &key_hook, mlx);
	mlx_loop_hook(mlx->mlx_p, raycasting, mlx);
	mlx_loop(mlx->mlx_p);
}

void	error_message(int num)
{
	if (num == 1)
		ft_printf("Error\nNumber of arguments incorrect\n");
	else if (num == 2)
		ft_printf("Error\nFile name incorrect\n");
	else if (num == 3)
		ft_printf("Error\nFile not found\n");
	else if (num == 4)
		ft_printf("Error\nEmpty map\n");
	else if (num == 5)
		ft_printf("Error\nEmpty line in map\n");
	else if (num == 6)
		ft_printf("Error\nElements number incorrect\n");
	else if (num == 7)
		ft_printf("Error\nMap not rectangular\n");
	else if (num == 8)
		ft_printf("Error\nWalls incorrect\n");
	else if (num == 9)
		ft_printf("Error\nWindow closed due to invalid path.\n");
	else if (num == 10)
		ft_printf("Error\nUnknown element\n");
}

int	wrong_input(char *filename, int inputnumber)
{
	char	*string;

	if (inputnumber != 2)
	{
		error_message(1);
		return (1);
	}
	string = ft_strrchr(filename, '.');
	if (string == 0)
	{
		error_message(2);
		return (1);
	}
	if (ft_strncmp(string, ".cub", 4) != 0)
	{
		error_message(2);
		return (1);
	}
	return (0);
}

int	open_file(t_mlx	*mlx, char *string)
{
	mlx->fd = open(string, O_RDONLY);
	if (mlx->fd < 0)
	{
		error_message(3);
		return (1);
	}
	return (0);
}

void	find_player(t_mlx *mlx, int i, int j)
{
	if (mlx->map_char[j][i] == 'N')
	{
		mlx->posX = i;
		mlx->posY = j;
		mlx->hasplayer++;
	}
}

void	measure_map(t_mlx *mlx, int i, int j)
{
	mlx->map_width = i;
	mlx->map_height = j;
}

void	analyse_map(t_mlx *mlx)
{
	int		i;
	int		j;

	mlx->hasplayer = 0;
	j = 0;
	while (mlx->map_char[j])
	{
		i = 0;
		while (mlx->map_char[j][i] != '\0')
		{
			find_player(mlx, i, j);
			i++;
		}
		j++;
	}
	measure_map(mlx, i, j);
}

void	copymap(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	mlx->map_int = malloc(sizeof(int *) * (mlx->map_height));
	while (i < mlx->map_height)
	{
		mlx->map_int[i] = malloc(sizeof(int) * (mlx->map_width));
		j = 0;
		while (j < mlx->map_width)
		{
			if (mlx->map_char[i][j] == 'N')
				mlx->map_int[i][j] = 0;
			else
				mlx->map_int[i][j] = mlx->map_char[i][j] - '0';
			j++;
		}
		i++;
	}
}

char	*ft_strdup_path(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	dest = (char *)malloc(i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strdup_digit(const char *s, int *j)
{
	char	*dest;
	int		i;
	int		final;

	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	dest = (char *)malloc(i + 1);
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		dest[i] = s[i];
		i++;
	}
	*j = *j + i;
	dest[i] = '\0';
	final = ft_atoi(dest);
	return (final);
}

int create_argb(int a, int r, int g, int b)
{
    return (a << 24 | r << 16 | g << 8 | b);
}

int	is_empty(t_mlx *mlx, char *temp, char *concat)
{
	int	i;

	i = 0;
	if (concat[0] == '\0')
	{
		error_message(4);
		free(temp);
		return (1);
	}
	while (concat[i] != '\0')
	{
		if (concat[i] == '\n' && concat[i + 1] == '\n')
		{
			error_message(5);
			free(temp);
			return (1);
		}
		i++;
	}
	mlx->map_char = ft_split(concat, '\n');
	free(concat);
	return (0);
}

int	store_map(t_mlx *mlx)
{
	char	*string;
	char	*temp;
	char	*concat;

	string = "1";
	concat = ft_strdup("");
	while (string)
	{
		string = NULL;
		temp = concat;
		string = get_next_line(mlx->fd);
		if (string)
		{
			concat = ft_strjoin(temp, string);
			free(string);
			free(temp);
		}
	}
	if (is_empty(mlx, temp, concat) == 1)
		return (1);
	return (0);
}

int	check_file(t_mlx *mlx)
{
	char	*string;
	char	*temp;
	char	*concat;
	int		i;

	while (1)
	{
		string = get_next_line(mlx->fd);
		if (string)
		{
			if (ft_strncmp(string, "NO", 2) == 0)
				mlx->path_north = ft_strdup_path(string + 3);
			else if (ft_strncmp(string, "SO", 2) == 0)
				mlx->path_south = ft_strdup_path(string + 3);
			else if (ft_strncmp(string, "WE", 2) == 0)
				mlx->path_west = ft_strdup_path(string + 3);
			else if (ft_strncmp(string, "EA", 2) == 0)
				mlx->path_east = ft_strdup_path(string + 3);
			else if (ft_strncmp(string, "F", 1) == 0)
			{
				i = 2;
				while (string[i] != '\0')
				{
					mlx->floor_r = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
					mlx->floor_g = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
					mlx->floor_b = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
				}
				mlx->floor_color = 	create_argb(0, mlx->floor_r, mlx->floor_g, mlx->floor_b);
			}
			else if (ft_strncmp(string, "C", 1) == 0)
			{
				i = 2;
				while (string[i] != '\0')
				{
					mlx->ceiling_r = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
					mlx->ceiling_g = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
					mlx->ceiling_b = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
				}
				mlx->ceiling_color = 	create_argb(0, mlx->ceiling_r, mlx->ceiling_g, mlx->ceiling_b);		
			}
			else if (ft_strrchr(string, '1'))
				break;
		}
		else
			break;
	}
	concat = ft_strdup("");
	temp = concat;
	concat = ft_strjoin(temp, string);
	free(string);
	free(temp);
	while (1)
	{
		string = NULL;
		temp = concat;
		string = get_next_line(mlx->fd);
		if (string)
		{
			concat = ft_strjoin(temp, string);
			free(string);
			free(temp);
		}
		else
			break;
	}
	if (is_empty(mlx, temp, concat) == 1)
		return (1);
	return (0);
}



int	main(int argc, char **argv)
{
	t_mlx	*mlx;


	mlx = malloc(sizeof(t_mlx));
	mlx->map_char = NULL;
	if (wrong_input(argv[1], argc) == 1)
		return (1);
	if (open_file(mlx, argv[1]) == 1)
		return (0);

	check_file(mlx);
	// if (store_map(mlx) == 1)
	// 	return (0);
	analyse_map(mlx);
	copymap(mlx);
	// check_map_int(mlx);
	// printf("%s\n", mlx->path_north);
	// printf("%s\n", mlx->path_south);
	// printf("%s\n", mlx->path_east);
	// printf("%s\n", mlx->path_west);
	init_values(mlx);
	init_minilibx(mlx);
	return (0);
}

// void check_map_int(t_mlx *mlx)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	// printf("[%d]", mlx->map_int[1][2]);
// 	while(i < mlx->map_height)
// 	{
// 		j = 0;
// 		while(j < mlx->map_width)
// 		{
// 			printf("%d", mlx->map_int[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

// void check_map_char(t_mlx *mlx)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while(mlx->map[i])
// 	{
// 		j = 0;
// 		while(mlx->map[i][j])
// 		{
// 			printf("%c", mlx->map[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

