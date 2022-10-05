/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/25 15:01:24 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*new;

	if (f && s)
	{
		len = ft_strlen(s);
		new = (char *) malloc((len + 1) * sizeof(char));
		if (new)
		{
			new[len] = 0;
			while (len && new)
			{
				new[len - 1] = f(len - 1, s[len - 1]);
				len--;
			}
			return (new);
		}		
	}
	return (NULL);
}
