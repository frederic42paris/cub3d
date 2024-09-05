#include "../minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define SW 640
#define SH 480
#define MAPW 24
#define MAPH 24
#define KEY_W	119
#define KEY_S	115
#define KEY_D	100
#define KEY_A	97

typedef struct s_mlx
{
	void	*mlx_p;
	void	*img;
	void	*win_ptr;
	char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
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
}	t_mlx;


int worldMap[MAPW][MAPH]=
{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void	draw_vertical_line(t_mlx *mlx, int x)
{
	int	y;

	y = mlx->drawStart;
	while (y <= mlx->drawEnd)
	{
		my_mlx_pixel_put(mlx, x, y, mlx->color);
		y++;
	}
}

void	raycasting(t_mlx *mlx)
{
	int	x;

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
			if (worldMap[mlx->mapX][mlx->mapY] > 0)
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

		//choose wall color
		if (worldMap[mlx->mapX][mlx->mapY] == 1)
			mlx->color = 0xFF0000;
		else if (worldMap[mlx->mapX][mlx->mapY] == 2)
			mlx->color = 0x00FF00;
		else if (worldMap[mlx->mapX][mlx->mapY] == 3)
			mlx->color = 0x0000FF;
		else if (worldMap[mlx->mapX][mlx->mapY] == 4)
			mlx->color = 0xFFFFFF;
		else
			mlx->color = 0xFFFF00;

		//give x and y sides different brightness
		if (mlx->side == 1)
			mlx->color = mlx->color / 2;

		//draw the pixels of the stripe as a vertical line
		draw_vertical_line(mlx, x);
		x++;
	}
}

int handle_key(int keycode, t_mlx *mlx) {
    // Clear the window
    
    if (keycode == 65307) // Escape key
        mlx_destroy_window(mlx->mlx_p, mlx->win_ptr);
    else if (keycode == KEY_D) // Right arrow key
    {

		mlx->oldDirX = mlx->dirX;
		mlx->dirX = mlx->dirX * cos(-mlx->rotSpeed) - mlx->dirY * sin(-mlx->rotSpeed);
		mlx->dirY = mlx->oldDirX * sin(-mlx->rotSpeed) + mlx->dirY * cos(-mlx->rotSpeed);
		mlx->oldPlaneX = mlx->planeX;
		mlx->planeX = mlx->planeX * cos(-mlx->rotSpeed) - mlx->planeY * sin(-mlx->rotSpeed);
		mlx->planeY = mlx->oldPlaneX * sin(-mlx->rotSpeed) + mlx->planeY * cos(-mlx->rotSpeed);
    mlx_clear_window(mlx->mlx_p, mlx->win_ptr);
		
		raycasting(mlx);
    mlx_put_image_to_window(mlx->mlx_p, mlx->win_ptr, mlx->img, 0, 0);

	}
    else if (keycode == KEY_A) // Left arrow key
    {

		mlx->oldDirX = mlx->dirX;
		mlx->dirX = mlx->dirX * cos(mlx->rotSpeed) - mlx->dirY * sin(mlx->rotSpeed);
		mlx->dirY = mlx->oldDirX * sin(mlx->rotSpeed) + mlx->dirY * cos(mlx->rotSpeed);
		mlx->oldPlaneX = mlx->planeX;
		mlx->planeX = mlx->planeX * cos(mlx->rotSpeed) - mlx->planeY * sin(mlx->rotSpeed);
		mlx->planeY = mlx->oldPlaneX * sin(mlx->rotSpeed) + mlx->planeY * cos(mlx->rotSpeed);
    mlx_clear_window(mlx->mlx_p, mlx->win_ptr);

		raycasting(mlx);
    mlx_put_image_to_window(mlx->mlx_p, mlx->win_ptr, mlx->img, 0, 0);

	}
    else if (keycode == KEY_S) // Down arrow key
    {

		if (!worldMap[(int)(mlx->posX - mlx->dirX * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX -= mlx->dirX * mlx->moveSpeed;
		if (!worldMap[(int)mlx->posX][(int)(mlx->posY - mlx->dirY * mlx->moveSpeed)])
			mlx->posY -= mlx->dirY * mlx->moveSpeed;
    mlx_clear_window(mlx->mlx_p, mlx->win_ptr);
	
		raycasting(mlx);
    mlx_put_image_to_window(mlx->mlx_p, mlx->win_ptr, mlx->img, 0, 0);

	}
    else if (keycode == KEY_W) // Up arrow key
    {
	
		if (!worldMap[(int)(mlx->posX + mlx->dirX * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX += mlx->dirX * mlx->moveSpeed;
		if (!worldMap[(int)mlx->posX][(int)(mlx->posY + mlx->dirY * mlx->moveSpeed)])
			mlx->posY += mlx->dirY * mlx->moveSpeed;
    mlx_clear_window(mlx->mlx_p, mlx->win_ptr);

		raycasting(mlx);
    mlx_put_image_to_window(mlx->mlx_p, mlx->win_ptr, mlx->img, 0, 0);

	}
    
    // Put the updated image to the window
    return 0;
}

void	init_values(t_mlx *mlx)
{
	mlx->posX = 22;
	mlx->posY = 12;
	mlx->dirX = -1;
	mlx->dirY = 0;
	mlx->planeX = 0;
	mlx->planeY = 0.66;
	mlx->time = 0;
	mlx->oldTime = 0;
	mlx->moveSpeed = 1;
	mlx->rotSpeed = 0.5;
}

int main() {

    t_mlx *mlx;
	mlx = malloc(sizeof(t_mlx));
	init_values(mlx);

    // Initialize mlx and create a new window
    mlx->mlx_p = mlx_init();
    mlx->win_ptr = mlx_new_window(mlx->mlx_p, SW, SH, "MiniLibX Image Update");

    // Create a new image
    mlx->img = mlx_new_image(mlx->mlx_p, SW, SH);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);

    // Initial draw
    raycasting(mlx); // White square
    mlx_put_image_to_window(mlx->mlx_p, mlx->win_ptr, mlx->img, 0, 0);

    // Handle key press events
    mlx_key_hook(mlx->win_ptr, handle_key, mlx);

    // Start the event loop
    mlx_loop(mlx->mlx_p);

    return 0;
}


// GONTJAROW - REMIX

/* typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 640, 360, "Hello world!");
	img.img = mlx_new_image(mlx, 640, 360);

	char *buffer = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.line_length, &img.endian);
	img.line_length /= 4;

	int color = 0xABCDEF;

	for(int y = 0; y < 360; ++y)
	for(int x = 0; x < 640; ++x)
	{
		buffer[(y * img.line_length) + x] = color;
	}

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
} */

// GONTJAROW 

/* int	main(void)
{
	int pixel_bits;
	int line_bytes;
	int endian;

	void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Create Image");
    void *image = mlx_new_image(mlx, 640, 360);

    char *buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	line_bytes /= 4;

	int color = 0xABCDEF;

	for(int y = 0; y < 360; ++y)
	for(int x = 0; x < 640; ++x)
	{
		buffer[(y * line_bytes) + x] = color;
	}

	mlx_put_image_to_window(mlx, win, image, 0, 0);
    mlx_loop(mlx);
} */

// INT TO RGB

/* 
int get_a(int argb)
{
    return ((argb >> 24) & 0xFF);
}

int get_r(int argb)
{
    return ((argb >> 16) & 0xFF);
}

int get_g(int argb)
{
    return ((argb >> 8) & 0xFF);
}

int get_b(int argb)
{
    return (argb & 0xFF);
}

int	main(void)
{
	int	result;

	result = get_r(16777215);
	printf("%d", result);
	return (0);
} */

// RGB to INT

/* int create_argb(int a, int r, int g, int b)
{
    return (a << 24 | r << 16 | g << 8 | b);
}

int	main(void)
{
	int	result;

	result = create_argb(0, 171, 205, 239);
	printf("%d", result);
	return (0);
} */

// HEX to INT

/* int	main(void)
{
	void	*mlx_ptr;
	int 	color;
	unsigned int	result;

	color = 0xABCDEF;
	mlx_ptr = mlx_init();
	result = mlx_get_color_value(mlx_ptr, color);
	printf("%x", result);
	return (0);
} */

// REACTIVE

/* typedef struct s_data
{
	void *mlx_ptr;
	void *win_ptr;
} t_data;
 
int on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}
 
int on_keypress(int keysym, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\\n", keysym);
	return (0);
}
 
int main(void)
{
	t_data data;
 
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "hi :)");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
 
	// Register key release hook
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
 
	// Register destroy hook
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
 
	// Loop over the MLX pointer
	mlx_loop(data.mlx_ptr);
	return (0);
} */

// 42 DOCS HOOKS

/* typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook!\n");
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
} */

// 42 DOCS EVENTS

/* typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	close(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
} */

// 42 DOCS INTRO

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_data	img;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
// 	img.img = mlx_new_image(mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img,
// 			&img.bits_per_pixel, &img.line_length, &img.endian);
// 	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_loop(mlx);
// }

// free  style

/* int main()
{
	void *mlx;
	void *win;
	void	*img;
	char	*relative_path = "./insta.xpm";
	int		img_width;
	int		img_height;

	img_height = 800;
	img_width = 800;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 800, "Tutorial Window");
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
} */

// 42 tutorial

/* void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	deal_key(int key, void *param)
{
	ft_putchar('X');
	return (0);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
} */