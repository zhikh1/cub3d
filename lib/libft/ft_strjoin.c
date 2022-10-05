/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/25 22:59:51 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	new_s = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	tmp = new_s;
	while ((*s2 || *s1) && new_s)
	{		
		if (*s1)
		{
			*tmp = *s1;
			s1++;
		}
		else
		{
			*tmp = *s2;
			s2++;
		}
		tmp++;
	}
	if (new_s)
		*tmp = 0;
	return (new_s);
}
