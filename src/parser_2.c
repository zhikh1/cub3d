/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:24:11 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/10 20:46:05 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/parser.h"

int	check_map_line_content(char *crnt_str, int line, int *player_cnt)
{
	int	char_type;

	while (*crnt_str)
	{
		char_type = is_map_char(*crnt_str);
		if (char_type == 0)
		{
			print_err_with_header(line, "Wrong symbol \"");
			ft_putchar_fd(*crnt_str, ERR_FD);
			ft_putstr_fd("\" in map!\nSymbols in map can be only: \
\"0\",\"1\",\" \",\"N\",\"S\",\"E\",\"W\".\n", ERR_FD);
			return (0);
		}
		if (char_type == 2)
			(*player_cnt)++;
		if (*player_cnt > 1)
		{
			print_err_with_header(line, "A map can only contain one player!\n");
			return (0);
		}
		crnt_str++;
	}
	return (1);
}

size_t	check_map_line_len(char *crnt_str, int *line_len, int *line)
{
	int	tmp_len;

	tmp_len = ft_strlen(crnt_str);
	if (crnt_str[tmp_len - 1] == '\n')
	{
		crnt_str[tmp_len - 1] = 0;
		tmp_len--;
	}
	if (tmp_len == 0)
	{
		print_err_with_header(*line, "Map cannot have empty fields!\n");
		return (0);
	}
	*line_len = tmp_len;
	return (1);
}

int	check_map(t_game *game, int map_file_fd, int *line)
{
	char	*crnt_str;
	int		line_len;
	int		player_cnt;

	player_cnt = 0;
	crnt_str = get_next_line(map_file_fd);
	(*line)++;
	while (crnt_str != NULL)
	{
		if (!check_map_line_len(crnt_str, &line_len, line))
			return (safe_free(crnt_str, 0));
		if (!check_map_line_content(crnt_str, *line, &player_cnt))
			return (safe_free(crnt_str, 0));
		if (game->map_size_x < line_len)
			game->map_size_x = line_len;
		game->map_size_y++;
		free(crnt_str);
		crnt_str = get_next_line(map_file_fd);
		(*line)++;
	}
	if (game->map_size_y == 0)
		print_err_with_header(*line, "Map cannot be empty!\n");
	else if (player_cnt == 0)
		print_err_with_header(*line, "The map must contain one player!\n");
	return (1);
}

char	*get_map_line(int map_file_fd, int map_line_size)
{
	char	*map_line;
	char	*map_str;
	int		map_str_len;

	map_str = get_next_line(map_file_fd);
	if (map_str == NULL)
	{
		ft_putstr_fd("Allocation fail!\n", ERR_FD);
		return (NULL);
	}
	map_line = malloc(sizeof(char) * map_line_size);
	if (map_line == NULL)
	{
		ft_putstr_fd("Allocation fail!\n", ERR_FD);
		safe_free(map_str, 0);
		return (NULL);
	}
	map_str_len = ft_strlen(map_str);
	if (map_str[map_str_len - 1] == '\n')
		map_str_len--;
	ft_memset(map_line, ' ', map_line_size);
	ft_memcpy(map_line, map_str, map_str_len);
	safe_free(map_str, 0);
	return (map_line);
}

void	search_player(t_game *game, int str_num)
{
	int		i;
	char	ch;

	i = 0;
	while (i < game->map_size_x)
	{
		ch = game->map[str_num][i];
		if (is_map_char(ch) == 2)
		{
			game->position.x = i;
			game->position.y = str_num;
			game->view_direction.x = (ch == 'W') * (-1.0) + (ch == 'E') * (1.0);
			game->view_direction.y = (ch == 'N') * (-1.0) + (ch == 'S') * (1.0);
			game->map[str_num][i] = '0';
		}
		i++;
	}
}
