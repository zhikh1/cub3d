/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/25 22:23:49 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	char	ch_fit;
	char	*byte_buf;
	size_t	i;

	i = 0;
	byte_buf = (char *)arr;
	ch_fit = c & 0xFF;
	while (i < n && byte_buf[i] != ch_fit)
		i++;
	if (i < n)
		if (byte_buf[i] == ch_fit)
			return (&byte_buf[i]);
	return (NULL);
}
