/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:30:10 by snunes            #+#    #+#             */
/*   Updated: 2019/06/28 12:03:21 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_nbr(const char *str, int *pos, va_list *ap)
{
	int result;

	if (str[*pos] == '*')
	{
		result = va_arg(*ap, int);
		(*pos)++;
		return (result);
	}
	result = 0;
	while (ft_isdigit(str[*pos]))
	{
		result *= 10;
		result += str[*pos] - 48;
		(*pos)++;
	}
	return (result);
}

int	find_conv(const char *str, int pos)
{
	int nb;

	nb = -1;
	if (str[pos] == 'c')
		nb = 1;
	else if (str[pos] == 's')
		nb = 2;
	else if (str[pos] == 'p')
		nb = 3;
	else if (str[pos] == 'd' || str[pos] == 'i')
		nb = 15;
	else if (str[pos] == 'o' || str[pos] == 'x' || str[pos] == 'X'
			|| str[pos] == 'u')
		nb = 15;
	else if (str[pos] == 'f' || str[pos] == 'F')
		nb = 13;
	else if (str[pos] == '%')
		nb = 18;
	else if (str[pos] == 'D' || str[pos] == 'U' || str[pos] == 'O')
		nb = 9;
	return (nb);
}

int	find_hhll(const char *str, t_flags *flag)
{
	int nb;
	int pos;

	order_flags(flag);
	pos = flag->spos;
	if (str[pos] == 'h' && str[pos + 1] == 'h' && (pos += 2) && (nb = 5))
		flag->conv = str[pos];
	else if (str[pos] == 'h' && (pos += 1) && (nb = 7))
		flag->conv = str[pos];
	else if (str[pos] == 'l' && str[pos + 1] == 'l' && (pos += 2) && (nb = 11))
		flag->conv = str[pos];
	else if ((str[pos] == 'l' || str[pos] == 'z') && (pos += 1)
			&& (str[pos] != 'f' && str[pos] != 'F') && (nb = 9))
		flag->conv = str[pos];
	else if (str[pos] == 'L' && (pos += 1) && (nb = 12))
		flag->conv = str[pos];
	else if (str[pos] == 'j' && (pos += 1) && (nb = 17))
		flag->conv = str[pos];
	else
		nb = find_conv(str, pos);
	flag->conv = str[pos];
	flag->spos = pos + 1;
	nb = (str[pos] == 'd' || str[pos] == 'i' || str[pos] == 'D') ? nb - 1 : nb;
	return (nb);
}

int	get_flag(const char *str, t_flags *flag, va_list *ap)
{
	int pos;

	if (!str[flag->spos])
		return (0);
	pos = flag->spos + 1;
	while (flag->spos != pos)
	{
		flag->spos = pos;
		if (str[pos] == '#' && ++pos)
			flag->diez = 1;
		if (str[pos] == '+' && ++pos)
			flag->plus = 1;
		if (str[pos] == ' ' && ++pos)
			flag->space = 1;
		if (str[pos] == '-' && ++pos)
			flag->minus = 1;
		if (str[pos] == '0' && ++pos)
			flag->zero = 1;
	}
	while (ft_isdigit(str[pos]) || str[pos] == '*')
		flag->width = get_nbr(str, &pos, ap);
	if (str[pos] == '.' && ++pos)
		flag->preci = get_nbr(str, &pos, ap);
	flag->spos = pos;
	return (find_hhll(str, flag));
}
