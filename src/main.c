/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:32:06 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/21 21:27:18 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	null_game(t_game *game)
{
	t_textures_index	i;

	if (game == NULL)
		return ;
	game->map = NULL;
	i = 0;
	while (i != TEXTURE_CNT)
	{
		game->textures_path[i] = NULL;
		i++;
	}
	game->map_size_x = 0;
	game->map_size_y = 0;
	game->ceilling_color = 0x0;
	game->floor_color = 0x0;
	game->position.x = 0.0;
	game->position.y = 0.0;
	game->view_direction.x = 0.0;
	game->view_direction.y = 0.0;
}

void	free_game(t_game *game)
{
	t_textures_index	i;

	if (game == NULL)
		return ;
	free_alloced_ptr_mas(&game->map, game->map_size_y);
	i = 0;
	while (i != TEXTURE_CNT)
	{
		safe_free(game->textures_path[i], 0);
		i++;
	}
	null_game(game);
}

int	generate_game(char const *map_file_path, t_game *game)
{
	if (game == NULL || map_file_path == NULL)
		return (0);
	return (1);
}

void	run_game(t_game *game)
{
	t_draw	draw;

	if (!check_map_walls(game))
	{
		free_game(game);
		exit (EXIT_FAILURE);
	}
	init(&draw, game);
	make_textures_addr(&draw, game);
	draw_map(&draw);
	mlx_hook(draw.mlx.win, 2, 1L << 0, &keys_handler, &draw);
	mlx_hook(draw.mlx.win, 17, 1L << 17, &stop_exit, &draw);
	mlx_loop(draw.mlx.mlx);
	exit_func(NULL, &draw);
}

int	main(int argc, char const *argv[])
{
	t_game	game;

	if (!check_params(argc, argv))
	{
		ft_putstr_fd("Wrong parameters! \n", ERR_FD);
		ft_putstr_fd("Usage: ./cub3d <map_file_path>.cub\n", ERR_FD);
		return (1);
	}
	null_game(&game);
	if (parce_map_file(&game, argv[1]))
		run_game(&game);
	free_game(&game);
	return (0);
}
