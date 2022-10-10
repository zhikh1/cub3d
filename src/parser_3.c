/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:24:57 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/10 20:46:08 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/parser.h"

int	skip_lines(int fd, int cnt)
{
	int		i;
	char	buf;

	i = 0;
	while (i < cnt)
	{
		if (read(fd, &buf, 1) < 0)
		{
			ft_putstr_fd("File read fail!\n", ERR_FD);
			return (0);
		}
		if (buf == '\n')
			i++;
	}
	return (1);
}

int	allocate_n_open_map(t_game *game, int *map_file_fd,
		char const *map_file_path)
{
	if (game->map == NULL)
	{
		ft_putstr_fd("Allocation fail!\n", ERR_FD);
		return (0);
	}
	*map_file_fd = open(map_file_path, O_RDONLY);
	if (*map_file_fd < 0)
	{
		safe_free(game->map, 0);
		perror(map_file_path);
		return (0);
	}
	return (1);
}

int	generate_map(t_game *game, char const *map_file_path)
{
	int	i;
	int	map_file_fd;

	i = 0;
	game->map = malloc(sizeof(char *) * game->map_size_y);
	if (!allocate_n_open_map(game, &map_file_fd, map_file_path))
		return (0);
	if (!skip_lines(map_file_fd, 8))
		return (close_fd_ret(map_file_fd, 0));
	while (i < game->map_size_y)
	{
		game->map[i] = get_map_line(map_file_fd,
				game->map_size_x);
		if (game->map[i] == NULL)
		{
			ft_putstr_fd("Allocation fail!\n", ERR_FD);
			free_alloced_ptr_mas(&game->map, i);
			return (close_fd_ret(map_file_fd, 0));
		}
		search_player(game, i);
		i++;
	}	
	return (close_fd_ret(map_file_fd, 1));
}

int	parce_map_file(t_game *game, char const *map_file_path)
{
	int	map_file_fd;
	int	line;

	line = 0;
	if (game == NULL || map_file_path == NULL)
		return (0);
	map_file_fd = open(map_file_path, O_RDONLY);
	if (map_file_fd < 0)
	{
		perror(map_file_path);
		return (0);
	}
	if (!parce_textures(game, map_file_fd, &line))
		return (close_fd_ret(map_file_fd, 0));
	if (!check_empty_line(map_file_fd, &line))
		return (close_fd_ret(map_file_fd, 0));
	if (!parce_ceilling_n_floor_colors(game, map_file_fd, &line))
		return (close_fd_ret(map_file_fd, 0));
	if (!check_empty_line(map_file_fd, &line))
		return (close_fd_ret(map_file_fd, 0));
	if (!check_map(game, map_file_fd, &line))
		return (close_fd_ret(map_file_fd, 0));
	if (!generate_map(game, map_file_path))
		return (close_fd_ret(map_file_fd, 0));
	return (close_fd_ret(map_file_fd, 1));
}

int	check_params(int argc, char const *argv[])
{
	size_t		map_file_path_len;
	size_t		file_extension_len;
	char const	*map_name;

	if (argc != 2 || argv == NULL)
		return (0);
	map_name = argv[1];
	map_file_path_len = ft_strlen(map_name);
	file_extension_len = ft_strlen(FILE_EXT);
	if (map_file_path_len < 5)
		return (0);
	if (ft_strcmp(&map_name[map_file_path_len - file_extension_len], FILE_EXT))
		return (0);
	return (1);
}
