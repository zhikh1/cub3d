/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:44:19 by cjanetta          #+#    #+#             */
/*   Updated: 2022/10/20 23:32:21 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_MAP_H
# define DRAW_MAP_H

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define FOV 0.6
# define SPD_P 0.6
# define SPD_R 0.2
# define ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define LEFT 65361
# define RIGHT 65363

# include "../mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include "../lib/libft/libft.h"
# include "game.h"
# include "main.h"

typedef struct s_ray
{
	int			step_x;
	int			step_y;
	int			i;
	int			vert_hit;
	t_vector	dir;
	t_vector	del;
	t_vector	sd;
}	t_ray;

typedef struct s_mlx
{
	void	*mlx;
	void	*img;
	void	*win;
	char	*addr;
	int		line_l;
	int		end;
	int		bitspp;
}	t_mlx;

typedef struct s_wall
{
	int		tex_x;
	double	tex_y;
	int		height;
	double	dist;
	int		top;
}	t_wall;

typedef struct s_draw
{
	t_mlx		mlx;
	t_ray		ray;
	t_game		*game;
	t_wall		wall;
	t_vector	plane;
	t_vector	rsp;
	int			*textures[TEXTURE_CNT];
}	t_draw;

void	draw_map(t_draw *draw);
void	init(t_draw *draw, t_game *game);
void	get_tex_pixels(int **addr, void *tex_img);
int		keys_handler(int key, t_draw *draw);
int		stop_exit(t_draw *draw);
void	exit_func(char *msg, t_draw *draw);
int		check_map_walls(t_game *game);
void	make_textures_addr(t_draw *draw, t_game *game);
void	get_wall_size(t_draw *draw);
void	get_pos_hit(t_draw *draw);
int		get_text_of_hit(t_draw *draw, int x, int y);
void	set_floor_ceil(t_draw *draw, int color, int start);
void	put_pixel_on_img(t_draw *draw, int x, int y, int color);
int		check_map_walls(t_game *game);

#endif