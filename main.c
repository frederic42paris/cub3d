/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 11:23:13 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	
	check_argument(argv[1], argc);
	mlx = malloc(sizeof(t_mlx));
	open_file(mlx, argv[1]);
	store_data(mlx);
	store_textures(mlx);
	analyse_map(mlx);
	store_map(mlx);
	display_parsing(mlx);
	return (0);
}
