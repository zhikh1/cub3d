/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2022/03/31 20:03:25 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	void	ft_filllen(char const *s, char c, char **new_mas)
{
	size_t	len;

	len = 0;
	if (new_mas && s)
	{
		while (*s)
		{
			while (*s == c && *s)
				s++;
			while (*s != c && *s)
			{
				s++;
				len++;
			}
			if ((*s == 0 && *(s - 1) != c) || *s)
			{			
				*new_mas = (char *)len;
				len = 0;
				new_mas++;
			}		
		}
		*new_mas = NULL;
	}
}

static	int	ft_fillptr(char **new_mas, size_t size)
{
	size_t	len;
	char	**head;

	head = new_mas;
	while (size > 0 && new_mas)
	{
		len = (size_t)(*new_mas);
		*new_mas = (char *) malloc(sizeof(char) * (len + 1));
		if (*new_mas == NULL)
		{
			while (head != new_mas)
			{
				free(*new_mas);
				new_mas--;
			}
			free(*head);
			free(head);
			return (0);
		}
		(*new_mas)[len] = 0;
		size--;
		new_mas++;
	}
	return (1);
}

static	void	ft_filldata(char const *s, char c, char **new_mas)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (s && new_mas)
	{
		while (*s)
		{
			if (*s != c)
			{
				new_mas[i][j] = *s;
				j++;
			}
			else if (*(s + 1) != c && j)
			{
				i++;
				j = 0;
			}	
			s++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	str_cnt;
	char	**new_mas;
	int		i;

	if (s && c)
	{
		str_cnt = ((*s != c) && (*s != 0));
		i = 0;
		while (s[i])
		{
			str_cnt += (s[i] == c && s[i + 1] != c && s[i + 1] != 0);
			i++;
		}
	}	
	else
		str_cnt = ((c == 0) && (*s != 0) && (s != 0));
	new_mas = (char **) malloc(sizeof(char *) * (str_cnt + 1));
	ft_filllen(s, c, new_mas);
	if (!ft_fillptr(new_mas, str_cnt))
		new_mas = NULL;
	if (!c && s && *s && new_mas)
		new_mas[0][ft_strlen(s)] = 0;
	ft_filldata(s, c, new_mas);
	return (new_mas);
}
