/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exept_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:53:28 by snunes            #+#    #+#             */
/*   Updated: 2019/06/28 12:25:14 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_zero(t_flags *fl, int sign)
{
	int len;
	int ret;

	fl->diez = (fl->preci > 0) ? 1 : fl->diez;
	len = 0;
	fl->len = fl->preci + 1 + fl->diez + fl->plus + (fl->space && sign);
	while (!fl->minus && fl->width-- > fl->len)
		len += write(fl->fd, " ", 1);
	len += (fl->space && sign) ? write(fl->fd, " ", 1) : 0;
	if (fl->plus)
		len += (sign == 0) ? write(fl->fd, "-", 1) : write(fl->fd, "+", 1);
	len += write(fl->fd, "0", 1);
	if (fl->diez)
		len += write(fl->fd, ".", 1);
	ret = fl->preci;
	while (ret--)
		len += write(fl->fd, "0", 1);
	if (fl->minus)
	{
		while (fl->width-- > fl->len)
			len += write(fl->fd, " ", 1);
	}
	return (len);
}

int	handle_exept(t_flags *flag, int nb_exept, int sign)
{
	int	fd;
	int len;

	fd = flag->fd;
	flag->plus = (sign == 0 && nb_exept != -3) ? 1 : flag->plus;
	len = 0;
	if (nb_exept == -1)
		return (handle_zero(flag, sign));
	if (!flag->minus)
	{
		while (flag->width-- > 3 + flag->plus)
			len += write(fd, " ", 1);
	}
	if (flag->plus && nb_exept != -3)
		len += (sign == 0) ? write(fd, "-", 1) : write(fd, "+", 1);
	if (flag->conv == 'f')
		len += (nb_exept == -2) ? write(fd, "inf", 3) : write(fd, "nan", 3);
	else if (flag->conv == 'F')
		len += (nb_exept == -2) ? write(fd, "INF", 3) : write(fd, "NAN", 3);
	if (flag->minus)
	{
		while (flag->width-- > 3 + flag->plus)
			len += write(fd, " ", 1);
	}
	return (len);
}

int	is_exept(char *mant, int exp)
{
	int		i;
	double	mantissa;
	double	pow;

	pow = 1;
	mantissa = 1;
	i = 2;
	while (mant[i])
	{
		pow /= 10;
		mantissa += (double)(mant[i++] - 48) * pow;
	}
	if (exp == -1023 && mantissa == 1)
		return (-1);
	if (exp == 1024 && mantissa == 1.5)
		return (-3);
	if (exp == 1024 && mantissa == 1)
		return (-2);
	return (0);
}
