/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:07 by nomargen          #+#    #+#             */
/*   Updated: 2021/10/25 15:00:52 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	size_t	len;
	int		buf;
	char	itoa[15];
	int		minus;

	minus = 1 - 2 * (n < 0);
	len = n <= 0;
	buf = n;
	while (buf)
	{
		buf /= 10;
		len++;
	}
	itoa[len] = 0;
	while (len)
	{
		itoa[len - 1] = (n % 10) * minus + '0';
		n /= 10;
		len--;
	}
	if (minus < 0)
		itoa[0] = '-';
	ft_putstr_fd(itoa, fd);
}
