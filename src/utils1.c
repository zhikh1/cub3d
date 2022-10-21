/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:25:49 by cjanetta          #+#    #+#             */
/*   Updated: 2022/10/21 21:32:03 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw_map.h"

void	make_textures_addr(t_draw *draw, t_game *game)
{
	int		i;
	void	*tex_img;
	int		arg[2];

	i = 0;
	while (i != TEXTURE_CNT)
	{
		tex_img = mlx_xpm_file_to_image(draw->mlx.mlx, game->textures_path[i],
				&arg[0], &arg[1]);
		if (arg[0] != 64 || arg[1] != 64 || !tex_img)
		{
			if (tex_img)
				mlx_destroy_image(draw->mlx.mlx, tex_img);
			exit_func("Error\nInvalid map\n", draw);
		}
		get_tex_pixels(&(draw->textures[i++]), tex_img);
		mlx_destroy_image(draw->mlx.mlx, tex_img);
	}
}

int	check_map_walls2(t_game *game, int i, int j)
{
	if (i == 0 || !(game->map[i - 1][j] == '1'
		|| game->map[i - 1][j] == '0'))
		return (0);
	if (j == 0 || !(game->map[i][j - 1] == '1'
		|| game->map[i][j - 1] == '0'))
		return (0);
	if (j == game->map_size_x - 1 || !(game->map[i][j + 1] == '1'
		|| game->map[i][j + 1] == '0'))
		return (0);
	if (i == game->map_size_y - 1 || !(game->map[i + 1][j] == '1'
		|| game->map[i + 1][j] == '0'))
		return (0);
	return (1);
}

int	check_map_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_size_y)
	{
		j = 0;
		while (j < game->map_size_x)
		{
			if (game->map[i][j] == '0')
			{
				if (!check_map_walls2(game, i, j))
				{
					print_err_with_header(i + 9,
						"The walls on the map are placed incorrectly!\n");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	exit_func(char *msg, t_draw *draw)
{
	free_game(draw->game);
	if (draw->textures[TEXTURE_INDEX_NORTH])
		free(draw->textures[TEXTURE_INDEX_NORTH]);
	if (draw->textures[TEXTURE_INDEX_SOUTH])
		free(draw->textures[TEXTURE_INDEX_SOUTH]);
	if (draw->textures[TEXTURE_INDEX_WEST])
		free(draw->textures[TEXTURE_INDEX_WEST]);
	if (draw->textures[TEXTURE_INDEX_EAST])
		free(draw->textures[TEXTURE_INDEX_EAST]);
	if (draw->mlx.img)
		mlx_destroy_image(draw->mlx.mlx, draw->mlx.img);
	if (draw->mlx.win)
		mlx_destroy_window(draw->mlx.mlx, draw->mlx.win);
	if (msg)
		ft_putstr_fd(msg, ERR_FD);
	exit(EXIT_FAILURE);
}

int	stop_exit(t_draw *draw)
{
	mlx_loop_end(draw->mlx.mlx);
	exit_func(NULL, draw);
	return (0);
}
