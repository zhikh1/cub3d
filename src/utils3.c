/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:27:54 by cjanetta          #+#    #+#             */
/*   Updated: 2022/10/21 20:54:51 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw_map.h"

void	get_wall_size(t_draw *draw)
{
	if (!draw->ray.vert_hit)
		draw->wall.dist = draw->ray.sd.x - draw->ray.del.x;
	else
		draw->wall.dist = draw->ray.sd.y - draw->ray.del.y;
	draw->wall.height = (int)(WIN_HEIGHT / draw->wall.dist);
	draw->wall.top = -draw->wall.height / 2 + WIN_HEIGHT / 2;
}

void	get_pos_hit(t_draw *draw)
{
	double	wall_x;

	if (!draw->ray.vert_hit)
		wall_x = draw->game->position.y + draw->wall.dist * draw->ray.dir.y;
	else
		wall_x = draw->game->position.x + draw->wall.dist * draw->ray.dir.x;
	wall_x -= floor(wall_x);
	draw->wall.tex_x = (int)(wall_x * 64.0);
	if ((!draw->ray.vert_hit && draw->ray.dir.x > 0)
		|| (draw->ray.vert_hit && draw->ray.dir.y < 0))
		draw->wall.tex_x = 64 - draw->wall.tex_x - 1;
}

int	get_text_of_hit(t_draw *draw, int x, int y)
{
	int	*tex;

	if (!draw->ray.vert_hit)
	{
		if (draw->ray.dir.x >= 0)
			tex = draw->textures[TEXTURE_INDEX_EAST];
		else
			tex = draw->textures[TEXTURE_INDEX_WEST];
	}
	else
	{
		if (draw->ray.dir.y >= 0)
			tex = draw->textures[TEXTURE_INDEX_SOUTH];
		else
			tex = draw->textures[TEXTURE_INDEX_NORTH];
	}
	return (tex[64 * y + x]);
}

void	set_floor_ceil(t_draw *draw, int color, int start)
{
	int	i;
	int	k;

	i = 0;
	while (i < (WIN_HEIGHT / 2))
	{
		k = 0;
		while (k < WIN_WIDTH)
		{
			put_pixel_on_img(draw, k, start + i, color);
			k++;
		}
		i++;
	}
}

void	draw_minimap(t_draw *draw)
{
	int		i;
	int		j;
	double	scale;

	scale = fminf(WIN_HEIGHT, WIN_WIDTH) / 3.0 / fmaxf(draw->game->map_size_x,
			draw->game->map_size_y);
	i = scale;
	i = 0;
	while (i < draw->game->map_size_x * scale)
	{
		j = 0;
		while (j < round(draw->game->map_size_y * scale))
		{
			if ((int)(draw->game->position.x) == (int)(i / scale)
					&& (int)(draw->game->position.y) == (int)(j / scale))
				put_pixel_on_img(draw, i, j, 0x00FF7F);
			else if (draw->game->map[(int)(j / scale)][(int)(i / scale)] == '1')
				put_pixel_on_img(draw, i, j, 0);
			else if (draw->game->map[(int)(j / scale)][(int)(i / scale)] == '0')
				put_pixel_on_img(draw, i, j, 0xCD853F);
			j++;
		}
		i++;
	}
}
