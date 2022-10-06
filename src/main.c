/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:32:06 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/06 23:22:50 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/main.h"

#include <stdio.h>

int	safe_free(void *ptr, int ret_val)
{
	if (ptr != NULL)
		free(ptr);
	return (ret_val);
}

int	print_err_with_header(int line, char *err_str)
{
	ft_putstr_fd("Error\nIn line #", ERR_FD);
	ft_putnbr_fd(line, ERR_FD);
	ft_putstr_fd(": ", ERR_FD);
	if (err_str != NULL)
		ft_putstr_fd(err_str, ERR_FD);
	return (0);
}

int	is_exist(char *file_name, int line)
{
	int		fd;

	if (file_name == NULL)
		return (0);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		print_err_with_header(line, NULL);
		perror(file_name);
		return (0);
	}
	close(fd);
	return (1);
}

void	print_field_err(char *crnt_str, char *parse_prefix, size_t parse_prefix_len, int line)
{
	print_err_with_header(line, NULL);
	if (crnt_str == NULL)
		ft_putstr_fd("Sudden end of file", ERR_FD);
	else
	{
		if (ft_strlen(crnt_str) > parse_prefix_len)
			crnt_str[parse_prefix_len] = 0;
		if (crnt_str[0] != 0)
		{
			ft_putstr_fd("Wrong field: \"", ERR_FD);
			ft_putstr_fd(crnt_str, ERR_FD);
			ft_putstr_fd("\"", ERR_FD);
		}
		else
			ft_putstr_fd("Empty field", ERR_FD);
	}
	ft_putstr_fd("!\nMust be: \"", ERR_FD);
	ft_putstr_fd(parse_prefix, ERR_FD);
	ft_putstr_fd("\"\n", ERR_FD);
}

int	check_field(char *crnt_str, char *parse_prefix, int line)
{
	size_t	parse_prefix_len;

	parse_prefix_len = ft_strlen(parse_prefix);
	if (crnt_str == NULL)
	{
		print_field_err(crnt_str, parse_prefix, parse_prefix_len, line);
		return (0);
	}
	parse_prefix_len = ft_strlen(parse_prefix);
	if (crnt_str[ft_strlen(crnt_str) - 1] == '\n')
	{
		crnt_str[ft_strlen(crnt_str) - 1] = 0;
	}
	if (ft_strncmp(crnt_str, parse_prefix, parse_prefix_len))
	{
		print_field_err(crnt_str, parse_prefix, parse_prefix_len, line);
		return (0);
	}
	return (1);
}

int	check_empty_line(int map_file_fd, int *line)
{
	char		*crnt_str;

	crnt_str = get_next_line(map_file_fd);
	(*line)++;
	if (crnt_str == NULL)
	{
		print_err_with_header(*line, "Sudden end of file!\n");
		return (0);
	}
	if (crnt_str[0] != '\n')
	{
		print_err_with_header(*line, "Line must be empty!\n");
		free(crnt_str);
		return (0);
	}
	free (crnt_str);
	return (1);
}

int	get_num_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]))
			return (i);
		i++;
	}
	return (i);
}

int	parse_rgb(int *rgb, char *crnt_str, int line)
{
	int	num_len;
	int	rgb_mas[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		num_len = get_num_len(crnt_str);
		if (num_len == 0 || crnt_str[0] == 0)
			return (print_err_with_header(line, "Wrong RGB format!\nMust be: \"<R>,<G>,<B>\"\n"));
		else if (num_len > 3 || ft_atoi(crnt_str) > 255)
			return (print_err_with_header(line, "Wrong RGB number range!\nMust be in range of 0-255\n"));
		else
			rgb_mas[i] = ft_atoi(crnt_str);
		if (i != 2 && crnt_str[num_len] != ',')
			return (print_err_with_header(line, "Wrong RGB format!\nMust be: \"<R>,<G>,<B>\"\n"));
		crnt_str += num_len + (i != 2);
		i++;
	}
	if (*crnt_str != 0)
		return (print_err_with_header(line, "There should be a new line after the numbers!\n"));
	*rgb = (rgb_mas[0] << 16 | rgb_mas[1] << 8 | rgb_mas[2]);
	return (1);
}

int	parce_ceilling_n_floor_colors(t_game *game, int map_file_fd, int *line)
{
	char		*crnt_str;
	int			i;
	static char	parse_prefix[2][4] = {"F ", "C "};
	int			*color_ptr;

	i = 0;
	while (i < 2)
	{
		crnt_str = get_next_line(map_file_fd);
		(*line)++;
		if (!check_field(crnt_str, parse_prefix[i], *line))
			return (safe_free(crnt_str, 0));
		if (i == 0)
			color_ptr = &game->floor_color;
		else
			color_ptr = &game->ceilling_color;
		if (!parse_rgb(color_ptr, &crnt_str[3], *line))
			return (safe_free(crnt_str, 0));
		free(crnt_str);
		i++;
	}
	return (game->map_size_x);
}

int	parce_textures(t_game *game, int map_file_fd, int *line)
{
	char				*crnt_str;
	static char			parse_prefix[4][4] = {"NO ", "SO ", "WE ", "EA "};
	t_textures_index	i;

	i = 0;
	while (i != TEXTURE_CNT)
	{
		crnt_str = get_next_line(map_file_fd);
		(*line)++;
		if (!check_field(crnt_str, parse_prefix[i], *line))
		{
			if (crnt_str != NULL)
				free(crnt_str);
			return (0);
		}
		if (!is_exist(&crnt_str[3], *line))
		{
			free(crnt_str);
			return (0);
		}
		game->textures_path[i] = ft_strdup(&crnt_str[3]);
		free(crnt_str);
		i++;
	}
	return (1);
}

int is_map_char(char ch)
{
	if (ch == '0' || ch == '1' || ch == ' ')
		return (1);
	if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
		return (2);
	return (0);
}

int	check_map_line_content(char *crnt_str, int line)
{
	while (*crnt_str)
	{
		if (!is_map_char(*crnt_str))
		{
			print_err_with_header(line, "Wrong symbol \"");
			ft_putchar_fd(*crnt_str, ERR_FD);
			ft_putstr_fd("\" in map!\nSymbols in map can be only:\
\"0\",\"1\",\" \",\"N\",\"S\",\"E\",\"W\".\n", ERR_FD);
			return (0);
		}
		crnt_str++;
	}
	return (1);
}

//доработать отсутствие карты
//проработать обнаружение игрока, его отсутствие и их избыток
int	check_map(t_game *game, int map_file_fd, int *line)
{
	char	*crnt_str;
	int		line_len;

	crnt_str = get_next_line(map_file_fd);
	(*line)++;
	while (crnt_str != NULL)
	{
		line_len = ft_strlen(crnt_str);
		if (crnt_str[line_len - 1] == '\n')
		{
			crnt_str[line_len - 1] = 0;
			line_len--;
		}
		if (line_len == 0)
			return (print_err_with_header(*line, "Map cannot have empty fields!\n"));
		if (!check_map_line_content(crnt_str, *line))
			return (safe_free(crnt_str, 0));
		if (game->map_size_x < line_len)
			game->map_size_x = line_len;
		game->map_size_y++;
		free(crnt_str);
		crnt_str = get_next_line(map_file_fd);
		(*line)++;
	}
	return (1);
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
		return (0);
	if (!check_empty_line(map_file_fd, &line))
		return (0);
	if (!parce_ceilling_n_floor_colors(game, map_file_fd, &line))
		return (0);
	if (!check_empty_line(map_file_fd, &line))
		return (0);
	if (!check_map(game, map_file_fd, &line))
		return (0);
	// generate_map(game, map_file_path);
	close(map_file_fd);
	return (1);
}

void	free_alloced_ptr_mas(char *mass[])
{
	int	i;

	if (mass == NULL)
		return ;
	i = 0;
	while (mass[i] != NULL)
	{
		free(mass[i]);
		i++;
	}
	free (mass);
}

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
	free_alloced_ptr_mas(game->map);
	i = 0;
	while (i != TEXTURE_CNT)
	{
		if (game->textures_path[i] != NULL)
		{
			free(game->textures_path[i]);
		}
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
	if (!parce_map_file(&game, argv[1]))
		return (1);
	// run_game(&game);
	free_game(&game);
	return (0);
}
