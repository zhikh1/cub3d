/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:27:02 by cjanetta          #+#    #+#             */
/*   Updated: 2022/10/20 23:26:33 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw_map.h"

void	get_tex_pixels(int **addr, void *tex_img)
{
	int	arg[3];
	int	*tmp;
	int	i;

	i = 0;
	tmp = (int *)mlx_get_data_addr(tex_img, &arg[0], &arg[1], &arg[2]);
	*addr = (int *)malloc(sizeof(int) * 4096);
	while (i < 4096)
	{
		(*addr)[i] = tmp[i];
		i++;
	}
}

void	init_mlx(t_draw *draw)
{
	draw->mlx.mlx = mlx_init();
	if (!draw->mlx.mlx)
		exit_func("Error\nMiniLibX error\n", draw);
	draw->mlx.win = mlx_new_window(draw->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"cub3D");
	if (!draw->mlx.win)
		exit_func("Error\nMiniLibX error\n", draw);
	draw->mlx.img = mlx_new_image(draw->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!draw->mlx.img)
		exit_func("Error\nMiniLibX error\n", draw);
	draw->mlx.addr = mlx_get_data_addr(draw->mlx.img, &draw->mlx.bitspp,
			&draw->mlx.line_l, &draw->mlx.end);
	if (!draw->mlx.addr)
		exit_func("Error\nMiniLibX error\n", draw);
}

void	init2(t_draw *draw)
{
	draw->plane.x = FOV;
	draw->plane.y = 0;
	draw->wall.height = 0;
	draw->wall.top = 0;
	draw->wall.tex_x = 0;
	draw->wall.tex_y = 0;
	draw->wall.dist = 0;
	draw->textures[TEXTURE_INDEX_NORTH] = NULL;
	draw->textures[TEXTURE_INDEX_SOUTH] = NULL;
	draw->textures[TEXTURE_INDEX_EAST] = NULL;
	draw->textures[TEXTURE_INDEX_WEST] = NULL;
	if (draw->game->view_direction.x == 1)
	{
		draw->plane.x = 0;
		draw->plane.y = FOV;
	}
	else if (draw->game->view_direction.x == -1)
	{
		draw->plane.x = 0;
		draw->plane.y = -FOV;
	}
	else if (draw->game->view_direction.y == 1)
		draw->plane.x = -FOV;
	init_mlx(draw);
}

void	init(t_draw *draw, t_game *game)
{
	draw->mlx.mlx = NULL;
	draw->mlx.win = NULL;
	draw->mlx.img = NULL;
	draw->mlx.addr = NULL;
	draw->mlx.bitspp = 0;
	draw->mlx.line_l = 0;
	draw->mlx.end = 0;
	draw->game = game;
	draw->ray.dir.x = 0;
	draw->ray.dir.y = 0;
	draw->ray.del.x = 0;
	draw->ray.del.y = 0;
	draw->ray.sd.x = 0;
	draw->ray.sd.y = 0;
	draw->ray.step_x = 0;
	draw->ray.step_y = 0;
	draw->ray.vert_hit = 0;
	init2(draw);
}

void	put_pixel_on_img(t_draw *draw, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = draw->mlx.addr + (y * draw->mlx.line_l + x
				* (draw->mlx.bitspp / 8));
		*(unsigned int *)dst = color;
	}
}
