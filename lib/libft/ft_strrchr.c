/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/25 22:46:40 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	ch_fit;
	char	*ch_find;

	ch_find = NULL;
	ch_fit = ch & 0xFF;
	while (*str)
	{
		if (*str == ch_fit)
			ch_find = (char *) str;
		str++;
	}
	if (!ch)
		ch_find = (char *)str;
	return (ch_find);
}
