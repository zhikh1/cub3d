/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:34:15 by nomargen          #+#    #+#             */
/*   Updated: 2022/03/06 15:21:55 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

long int	ft_atol(const char *str)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	if (str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '-' || *str == '+')
		{
			sign = (*str == '+') - (*str == '-');
			str++;
		}
		while (ft_isdigit(*str))
		{
			num = (num * 10) + (*str - '0');
			str++;
		}		
	}
	return (num * sign);
}
