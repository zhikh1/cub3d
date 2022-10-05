/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2022/02/20 22:06:45 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstsize;

	dstsize = ft_strlen(dst);
	if (dst && src)
	{
		i = dstsize;
		j = 0;
		while (i < size && src[j])
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		if (dstsize < size)
			dst[i - (i >= size)] = 0;
	}
	return (ft_strlen(src) + (size) * (size <= dstsize)
		+ (dstsize) * (size > dstsize));
}
