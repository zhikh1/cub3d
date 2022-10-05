/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/25 22:28:14 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t count)
{
	size_t			i;
	unsigned char	*byte_buf1;
	unsigned char	*byte_buf2;

	byte_buf1 = (unsigned char *)buf1;
	byte_buf2 = (unsigned char *)buf2;
	i = 0;
	while (i < count - 1 && byte_buf1[i] == byte_buf2[i])
		i++;
	return ((byte_buf1[i] - byte_buf2[i])
		* (byte_buf1[i] != byte_buf2[i]) * (i < count));
}
