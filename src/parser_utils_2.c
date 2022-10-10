/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:20:50 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/10 20:46:13 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/parser.h"

void	free_alloced_ptr_mas(char **mass[], size_t size)
{
	size_t	i;

	if (*mass == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		free((*mass)[i]);
		i++;
	}
	free (*mass);
	*mass = NULL;
}

int	close_fd_ret(int fd, int ret)
{
	if (fd >= 0)
		close(fd);
	return (ret);
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
