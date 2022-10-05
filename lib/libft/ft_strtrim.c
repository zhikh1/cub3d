/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/25 23:08:45 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	ft_isset(char const *set, char c)
{
	int	result;

	result = 0;
	if (set)
	{
		while (*set)
		{
			if (*set == c)
			{
				result = 1;
				break ;
			}
			set++;
		}
	}
	return (result);
}

static	void	dumb(size_t begin, size_t end, char *trim, char const *s1)
{
	size_t	i;

	i = 0;
	while (begin <= end)
	{
		trim[i] = s1[begin];
		begin++;
		i++;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	begin;
	size_t	end;	

	trim = NULL;
	begin = 0;
	if (s1)
	{
		while (ft_isset(set, s1[begin]) && s1[begin])
			begin++;
		end = ft_strlen(s1);
		while (ft_isset(set, s1[end - 1]) && (end > begin))
			end--;
		trim = (char *) malloc(sizeof(char) * (end - begin + 1));
		if (trim)
		{
			dumb(begin, end, trim, s1);
			trim[end - begin] = 0;
		}
	}
	return (trim);
}
