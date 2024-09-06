/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/06 19:14:30 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	simple_parsing_fred(t_mlx *mlx)
{
	parse_elements(mlx);
	parse_map(mlx);
	// check_file(mlx);
	analyse_map(mlx);
	copymap(mlx);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->map_char = NULL;
	if (check_argument(argv[1], argc) == 1)
		return (1);
	if (open_file(mlx, argv[1]) == 1)
		return (1);
	// parsing
	// simple_parsing_fred(mlx);
	parser(argv[1], mlx);
	// parsing result
	// display_parsing(mlx);
	// free(mlx);
	return (0);
}
