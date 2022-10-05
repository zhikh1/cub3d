/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/30 03:25:58 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	fact_len;
	size_t	s_len;
	char	*sub_s;

	if (s)
	{
		s_len = ft_strlen(s);
		if (s_len <= start)
			return (ft_strdup(""));
		fact_len = ft_strlen(s + start) * (s_len >= start);
		if (fact_len > len)
			fact_len = len;
		sub_s = (char *) malloc((fact_len + 1) * sizeof(char));
		if (sub_s)
			sub_s[fact_len] = 0;
		while (fact_len > 0 && sub_s)
		{
			sub_s[fact_len - 1] = s[fact_len - 1 + start];
			fact_len--;
		}		
		return (sub_s);
	}
	else
		return (NULL);
}
