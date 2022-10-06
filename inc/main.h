/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 20:40:25 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/06 22:59:22 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "../lib/libft/libft.h"
#include "../inc/get_next_line.h"

#define FILE_EXT (".cub")
#define ERR_FD (2)

typedef enum texture_index_e
{
	TEXTURE_INDEX_NORTH = 0,
	TEXTURE_INDEX_SOUTH,
	TEXTURE_INDEX_WEST,
	TEXTURE_INDEX_EAST,

	TEXTURE_CNT
}	t_textures_index;

typedef struct position_s
{
	double	x;
	double	y;
}	t_vector;

typedef struct game_s
{
	char		**map;
	int			map_size_x;
	int			map_size_y;
	char		*textures_path[TEXTURE_CNT];
	int			ceilling_color;
	int			floor_color;
	t_vector	position;
	t_vector	view_direction;
}	t_game;

#endif