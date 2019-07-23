/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_wdouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:51:29 by snunes            #+#    #+#             */
/*   Updated: 2019/06/28 12:47:41 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_round(char *mant, int bound)
{
	int		i;
	int		unit;
	char	two[55];

	ft_bzero(two, 55);
	two[0] = '1';
	i = bound;
	unit = mant[i] - 48;
	if (unit >= 5 && mant[--i] != '.')
	{
		unit = mant[i] - 47;
		mant[i--] = (unit % 10) + 48;
		while (unit > 9 && mant[i] && mant[i] != '.')
		{
			unit = mant[i] - 47;
			mant[i] = (unit % 10) + 48;
			--i;
		}
	}
	if (mant[i] == '.')
		ft_add(mant, two);
	return ((mant[i] == '.') ? 1 : 0);
}

void	char_to_bits(char c, char *mant, char *two, int nb)
{
	int i;
	int gap;

	gap = (nb == 6) ? 8 : 128;
	while (gap > 0)
	{
		i = (c & gap);
		if (i >= 1)
			ft_add(mant, two);
		gap /= 2;
		ft_divide(two);
	}
}

int		create_doub(char *bits, char *mant)
{
	int		i;
	int		exp;
	char	two[56];

	ft_bzero(two, sizeof(two));
	ft_strcat(two, "0.5\0");
	exp = ((bits[7] & 0x7F) << 4) + ((bits[6] & 0xF0) >> 4) - 1023;
	i = 6;
	while (i > -1)
	{
		char_to_bits(bits[i], mant, two, i);
		i--;
	}
	if ((i = is_exept(mant, exp)) < 0)
		return (i);
	while (exp > 0)
	{
		ft_multiply(mant);
		exp--;
	}
	while (exp++ < 0)
		ft_divide(mant);
	return (0);
}
