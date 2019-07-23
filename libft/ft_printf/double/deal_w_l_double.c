/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_w_L_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:38:11 by snunes            #+#    #+#             */
/*   Updated: 2019/06/28 11:20:55 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_l_exept(int exp, char *mant, int int_p)
{
	int			i;
	long double	mantissa;
	long double	pow;

	pow = 1;
	i = 2;
	mantissa = 1;
	while (mant[i])
	{
		pow /= 10;
		mantissa += (long double)(mant[i++] - 48) * pow;
	}
	if (exp == -16383 && !int_p && mantissa == 1)
		return (-1);
	if (exp == 16384 && !int_p && mantissa == 1)
		return (-2);
	if (exp == 16384 && !int_p && mantissa != 1)
		return (-3);
	if (exp == 16384 && mant[2] >= '5')
		return (-3);
	if (exp == 16384 && int_p && mantissa == 1)
		return (-2);
	if (exp == 16384 && int_p && mantissa != 1)
		return (-3);
	return (0);
}

void	char_to_bits2(char c, char *mant, char *two, int nb)
{
	int i;
	int gap;

	gap = (nb == 7) ? 64 : 128;
	while (gap > 0)
	{
		i = (c & gap);
		if (i >= 1)
			ft_add(mant, two);
		gap /= 2;
		ft_divide(two);
	}
}

int		create_l_doub(char *bits, char *mant)
{
	int		i;
	int		exp;
	char	two[67];

	i = 7;
	ft_bzero(two, sizeof(two));
	ft_strcat(two, "0.5\0");
	exp = ((bits[9] & 127) << 8) + (bits[8] & 255) - 16383;
	while (i > -1)
	{
		char_to_bits2(bits[i], mant, two, i);
		i--;
	}
	i = (bits[7] & 128) > 0;
	if ((i = is_l_exept(exp, mant, i)) < 0)
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
