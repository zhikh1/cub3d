/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/25 14:59:57 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	void	ft_itoa_fill(char *itoa, size_t len, int n, int minus)
{
	itoa[len] = 0;
	while (len)
	{
		itoa[len - 1] = (n % 10) * minus + '0';
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	size_t	len;
	int		buf;
	char	*itoa;
	int		minus;

	minus = 1 - 2 * (n < 0);
	len = n <= 0;
	buf = n;
	while (buf)
	{
		buf /= 10;
		len++;
	}
	itoa = (char *) malloc((len + 1) * sizeof(char));
	if (itoa)
		ft_itoa_fill(itoa, len, n, minus);
	if (minus < 0 && itoa)
		itoa[0] = '-';
	return (itoa);
}
