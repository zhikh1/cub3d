/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:21:59 by cjanetta          #+#    #+#             */
/*   Updated: 2022/10/20 23:38:19 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw_map.h"

void	down_up(int keykode, t_draw *draw)
{
	if (keykode == KEY_W)
	{
		if (draw->game->map[(int)(draw->game->position.y)]
			[(int)(draw->game->position.x
				+ draw->game->view_direction.x * SPD_P)] == '0')
			draw->game->position.x += draw->game->view_direction.x * SPD_P;
		if (draw->game->map[(int)(draw->game->position.y
				+ draw->game->view_direction.y * SPD_P)]
			[(int)(draw->game->position.x)] == '0')
			draw->game->position.y += draw->game->view_direction.y * SPD_P;
	}
	if (keykode == KEY_S)
	{
		if (draw->game->map[(int)(draw->game->position.y)]
			[(int)(draw->game->position.x -
				draw->game->view_direction.x * SPD_P)] == '0')
			draw->game->position.x -= (draw->game->view_direction.x * SPD_P);
		if (draw->game->map[(int)(draw->game->position.y
				- draw->game->view_direction.y * SPD_P)]
			[(int)(draw->game->position.x)] == '0')
			draw->game->position.y -= (draw->game->view_direction.y * SPD_P);
	}
	draw_map(draw);
}

void	right_left(int keykode, t_draw *draw)
{
	if (keykode == KEY_D)
	{
		if (draw->game->map[(int)(draw->game->position.y)]
			[(int)(draw->game->position.x + draw->plane.x * SPD_P)] == '0')
			draw->game->position.x += draw->plane.x * SPD_P;
		if (draw->game->map[(int)(draw->game->position.y
				+ draw->plane.y * SPD_P)]
			[(int)(draw->game->position.x)] == '0')
			draw->game->position.y += draw->plane.y * SPD_P;
	}
	if (keykode == KEY_A)
	{
		if (draw->game->map[(int)(draw->game->position.y)]
			[(int)(draw->game->position.x - draw->plane.x * SPD_P)] == '0')
			draw->game->position.x -= draw->plane.x * SPD_P;
		if (draw->game->map[(int)(draw->game->position.y
				- draw->plane.y * SPD_P)]
			[(int)(draw->game->position.x)] == '0')
			draw->game->position.y -= draw->plane.y * SPD_P;
	}
	draw_map(draw);
}

void	rotate2(int keykode, t_draw *draw, double old_dirx, double old_planex)
{
	if (keykode == RIGHT)
	{
		draw->game->view_direction.x = draw->game->view_direction.x * cos(SPD_R)
			- draw->game->view_direction.y * sin(SPD_R);
		draw->game->view_direction.y = old_dirx * sin(SPD_R)
			+ draw->game->view_direction.y * cos(SPD_R);
		draw->plane.x = draw->plane.x * cos(SPD_R) - draw->plane.y * sin(SPD_R);
		draw->plane.y = old_planex * sin(SPD_R) + draw->plane.y * cos(SPD_R);
	}
}

void	rotate(int keykode, t_draw *draw)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = draw->game->view_direction.x;
	old_planex = draw->plane.x;
	if (keykode == LEFT)
	{
		draw->game->view_direction.x = draw->game->view_direction.x
			* cos(-SPD_R)
			- draw->game->view_direction.y * sin(-SPD_R);
		draw->game->view_direction.y = old_dirx * sin(-SPD_R)
			+ draw->game->view_direction.y * cos(-SPD_R);
		draw->plane.x = draw->plane.x * cos(-SPD_R) - draw->plane.y
			* sin(-SPD_R);
		draw->plane.y = old_planex * sin(-SPD_R) + draw->plane.y * cos(-SPD_R);
	}
	rotate2(keykode, draw, old_dirx, old_planex);
	draw_map(draw);
}

int	keys_handler(int keykode, t_draw *draw)
{
	if (keykode == ESC)
	{
		mlx_loop_end(draw->mlx.mlx);
		exit_func(NULL, draw);
	}
	else if (keykode == KEY_A || keykode == KEY_D)
		right_left(keykode, draw);
	else if (keykode == KEY_W || keykode == KEY_S)
		down_up(keykode, draw);
	else if (keykode == LEFT || keykode == RIGHT)
		rotate(keykode, draw);
	return (0);
}
