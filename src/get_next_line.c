/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 17:14:53 by cjanetta          #+#    #+#             */
/*   Updated: 2022/10/20 23:36:54 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

static void	ft_con(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free (tmp);
}

static void	ft_move_buf(char **buf, int index)
{
	char	*tmp;

	tmp = *buf;
	(*buf)[index] = '\n';
	*buf = ft_substr(*buf, index + 1, BUFFER_SIZE);
	free (tmp);
}

static int	ft_read(int fd, char **buf)
{
	int	ret;

	if (*buf)
	{
		free (*buf);
		*buf = (void *)0;
	}
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buf)
		return (0);
	ret = read(fd, *buf, BUFFER_SIZE);
	if (ret <= 0)
	{
		free (*buf);
		*buf = (void *)0;
		return (0);
	}
	(*buf)[ret] = '\0';
	return (1);
}

static char	*ft_gnl(int fd, char **buf)
{
	char	*line;
	int		count;

	count = 0;
	line = (char *)malloc(sizeof(char));
	line[count] = '\0';
	if (!line)
		return ((void *)0);
	while ((*buf)[count] != '\n')
	{
		if ((*buf)[count] == '\0')
		{
			ft_con(&line, *buf);
			if (!ft_read(fd, buf))
				return (line);
			count = 0;
		}
		else
			count++;
	}
	(*buf)[count] = '\0';
	ft_con(&line, *buf);
	ft_con(&line, "\n");
	ft_move_buf(buf, count);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0)
		return ((void *)0);
	if (!buf)
		if (!ft_read(fd, &buf))
			return ((void *)0);
	line = ft_gnl(fd, &buf);
	if (line[0] == '\0')
	{
		free (line);
		return ((void *)0);
	}
	else
		return (line);
}
