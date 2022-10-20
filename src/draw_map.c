/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:46:03 by cjanetta          #+#    #+#             */
/*   Updated: 2022/10/20 23:53:44 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw_map.h"

void	create_ray2(t_draw *draw)
{
	draw->ray.step_x = 1;
	draw->ray.sd.x = (draw->rsp.x + 1.0 - draw->game->position.x)
		* draw->ray.del.x;
	draw->ray.step_y = 1;
	draw->ray.sd.y = (draw->rsp.y + 1.0 - draw->game->position.y)
		* draw->ray.del.y;
	if (draw->ray.dir.x < 0)
	{
		draw->ray.step_x = -1;
		draw->ray.sd.x = (draw->game->position.x - draw->rsp.x)
			* draw->ray.del.x;
	}
	if (draw->ray.dir.y < 0)
	{
		draw->ray.step_y = -1;
		draw->ray.sd.y = (draw->game->position.y - draw->rsp.y)
			* draw->ray.del.y;
	}
}

void	create_ray(t_draw *draw)
{
	double	camera_x;

	camera_x = draw->ray.i * 2.0 / (double)WIN_WIDTH - 1.0;
	draw->ray.dir.x = draw->game->view_direction.x + draw->plane.x * camera_x;
	draw->ray.dir.y = draw->game->view_direction.y + draw->plane.y * camera_x;
	draw->rsp.x = (int)draw->game->position.x;
	draw->rsp.y = (int)draw->game->position.y;
	draw->ray.del.x = fabs(1.0 / draw->ray.dir.x);
	draw->ray.del.y = fabs(1.0 / draw->ray.dir.y);
	create_ray2(draw);
}

void	start_ray(t_draw *draw)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (draw->ray.sd.x < draw->ray.sd.y)
		{
			draw->ray.sd.x += draw->ray.del.x;
			draw->rsp.x += draw->ray.step_x;
			draw->ray.vert_hit = 0;
		}
		else
		{
			draw->ray.sd.y += draw->ray.del.y;
			draw->rsp.y += draw->ray.step_y;
			draw->ray.vert_hit = 1;
		}
		if (draw->game->map[(int)draw->rsp.y][(int)draw->rsp.x] == '1')
			hit = 1;
	}
}

void	draw_line(t_draw *draw)
{
	double	scale;
	int		color;
	int		i;

	scale = 64.0 / (double)draw->wall.height;
	draw->wall.tex_y = 0;
	i = 0;
	while (i < draw->wall.height)
	{
		color = get_text_of_hit(draw, draw->wall.tex_x, (int)draw->wall.tex_y);
		put_pixel_on_img(draw, draw->ray.i, draw->wall.top + i, color);
		draw->wall.tex_y += scale;
		i++;
	}
}

void	draw_map(t_draw *draw)
{
	draw->ray.i = 0;
	set_floor_ceil(draw, draw->game->ceilling_color, 0);
	set_floor_ceil(draw, draw->game->floor_color, WIN_HEIGHT / 2);
	while (draw->ray.i < WIN_WIDTH)
	{
		create_ray(draw);
		start_ray(draw);
		get_wall_size(draw);
		get_pos_hit(draw);
		draw_line(draw);
		draw->ray.i++;
	}
	mlx_put_image_to_window(draw->mlx.mlx, draw->mlx.win, draw->mlx.img, 0, 0);
}
