/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/25 15:00:31 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	void	*ft_rev_memcpy(void *destptr, const void *srcptr, size_t num)
{
	char		*dest_buf;
	const char	*src_buf;

	dest_buf = destptr;
	src_buf = srcptr;
	while (num > 0)
	{
		dest_buf[num - 1] = src_buf[num - 1];
		num--;
	}
	return (destptr);
}

void	*ft_memmove(void *destptr, const void *srcptr, size_t num)
{		
	if (!destptr && !srcptr)
		return (NULL);
	if (srcptr > destptr)
	{
		ft_memcpy(destptr, srcptr, num);
	}
	else
	{
		ft_rev_memcpy(destptr, srcptr, num);
	}
	return (destptr);
}
