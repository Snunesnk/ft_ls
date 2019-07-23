/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 06:42:02 by simon             #+#    #+#             */
/*   Updated: 2019/04/24 15:07:07 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_length(int n)
{
	long	power;
	int		length;

	power = 10;
	length = 1;
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		length++;
		n = -1 * n;
	}
	while (power <= n)
	{
		power = power * 10;
		length++;
	}
	return (length);
}

static char	*ft_fill_str(char *str, int n, int i, int length)
{
	long	power;

	power = 10;
	while (power <= n)
		power = power * 10;
	while (i < length)
	{
		power = power / 10;
		str[i] = (n / power) % 10 + 48;
		i++;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		length;

	length = ft_length(n);
	i = 0;
	if (!(str = (char *)ft_memalloc(sizeof(*str) * length + 1)))
		return (NULL);
	if (n < 0)
	{
		str[i] = '-';
		i++;
		if (n == -2147483648)
		{
			str[i] = '2';
			i++;
			n = -1 * (n + 2000000000);
		}
		else
			n = -1 * n;
	}
	str = ft_fill_str(str, n, i, length);
	return (str);
}
