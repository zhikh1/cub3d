/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:18:49 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/10 20:46:11 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/parser.h"

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

void	print_field_err(char *crnt_str, char *parse_prefix,
		size_t parse_prefix_len, int line)
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

int	is_map_char(char ch)
{
	if (ch == '0' || ch == '1' || ch == ' ')
		return (1);
	if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
		return (2);
	return (0);
}
