/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:03:03 by snunes            #+#    #+#             */
/*   Updated: 2019/06/28 12:46:03 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_shiftstr(char *buff, int mode)
{
	int i;
	int ret_mv;
	int ret_curr;

	i = 0;
	ret_mv = (mode == 1) ? buff[i] : buff[i + 1];
	if (mode == 1)
		buff[i] = '0';
	while (buff[i])
	{
		if (mode == 1)
			i++;
		ret_curr = (mode == 1) ? buff[i] : buff[i + 2];
		buff[i] = ret_mv;
		ret_mv = ret_curr;
		if (mode == 2)
			i++;
	}
	buff[i] = 0;
}

int		ft_multiply(char *buff)
{
	int len;
	int unit;

	len = 0;
	while (buff[len])
		len++;
	while (len > 0)
	{
		len = (buff[len - 1] == '.') ? len - 2 : len - 1;
		unit = (buff[len] - 48) * 2;
		buff[len] = unit % 10 + 48;
		while (unit > 9)
		{
			len = (buff[len - 1] == '.') ? len - 2 : len - 1;
			if (len < 0)
			{
				ft_shiftstr(buff, 1);
				buff[0] = buff[0] + 1;
				return (1);
			}
			unit = (buff[len] - 48) * 2 + 1;
			buff[len] = unit % 10 + 48;
		}
	}
	return (0);
}

void	ft_divide(char *buff)
{
	int len;
	int ret;
	int dot;
	int	unit;

	dot = 0;
	while (buff[dot] && buff[dot] != '.')
		dot++;
	len = 0;
	ret = 0;
	while (buff[len])
	{
		unit = buff[len] - 48;
		buff[len] = (unit / 2 + 48) + ret;
		ret = (unit / 2 * 2 != unit) ? 5 : 0;
		len = (buff[len + 1] == '.') ? len + 2 : len + 1;
	}
	if (ret == 5)
	{
		if (len == dot)
			buff[len++] = '.';
		buff[len++] = '5';
	}
	while (buff[0] == '0' && buff[1] != '.')
		ft_shiftstr(buff, 2);
}

int		ft_align(char *buff, char *two)
{
	int t_len;
	int b_len;
	int len;

	len = 0;
	t_len = 0;
	b_len = 0;
	while (two[t_len] != '.' && two[t_len])
		t_len++;
	while (buff[b_len] != '.' && buff[b_len])
		b_len++;
	while (t_len > b_len)
	{
		ft_shiftstr(buff, 1);
		t_len--;
	}
	while (b_len > t_len)
	{
		ft_shiftstr(two, 1);
		b_len--;
	}
	while (buff[len] || two[len])
		len++;
	return (len - 1);
}

int		ft_add(char *buff, char *two)
{
	int ret;
	int nb;
	int len;

	len = ft_align(buff, two);
	ret = 0;
	while (len >= 0)
	{
		nb = (buff[len] != 0) ? buff[len] - 48 + ret : ret;
		nb += (two[len] != 0) ? two[len] - 48 : 0;
		ret = (nb < 10) ? 0 : 1;
		if (nb < 10)
			buff[len] = nb + 48;
		else
			buff[len] = nb % 10 + 48;
		len = (buff[len - 1] == '.') ? len - 2 : len - 1;
	}
	if (ret != 0)
	{
		ft_shiftstr(buff, 1);
		buff[0] = ret + 48;
	}
	return (0);
}
