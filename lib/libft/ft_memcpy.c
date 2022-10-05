/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/25 15:00:28 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *destptr, const void *srcptr, size_t num)
{
	size_t		i;
	char		*dest_buf;
	const char	*src_buf;

	dest_buf = destptr;
	src_buf = srcptr;
	i = 0;
	if (!destptr && !srcptr)
		return (NULL);
	while (i < num)
	{
		dest_buf[i] = src_buf[i];
		i++;
	}
	return (destptr);
}
