/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 12:21:59 by snunes            #+#    #+#             */
/*   Updated: 2019/06/28 11:47:02 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_l_int(t_flags *flag, va_list *ap)
{
	long int nbr;

	nbr = va_arg(*ap, long int);
	if (flag->conv == 'd' || flag->conv == 'i' || flag->conv == 'D')
		return (print_nb(flag, nbr, 10));
	if (flag->conv == 'U')
		return (print_unb(flag, nbr, 10));
	if (flag->conv == 'o' || flag->conv == 'O')
		return (print_unb(flag, nbr, 8));
	if (flag->conv == 'x' || flag->conv == 'X')
		return (print_unb(flag, nbr, 16));
	return (-1);
}

int	get_ll_int(t_flags *flag, va_list *ap)
{
	long long int nbr;

	nbr = va_arg(*ap, long long int);
	if (flag->conv == 'd' || flag->conv == 'i' || flag->conv == 'D')
		return (print_nb(flag, nbr, 10));
	if (flag->conv == 'U')
		return (print_unb(flag, nbr, 10));
	if (flag->conv == 'o' || flag->conv == 'O')
		return (print_unb(flag, nbr, 8));
	if (flag->conv == 'x' || flag->conv == 'X')
		return (print_unb(flag, nbr, 16));
	return (-1);
}

int	get_l_double(t_flags *flag, va_list *ap)
{
	char		*bits;
	long double	nbr;
	char		mant[6000];
	char		*espaces;
	char		att[5];

	flag->len = 0;
	flag->preci = (flag->preci < 0) ? 6 : flag->preci;
	ft_bzero(mant, sizeof(mant));
	mant[0] = '1';
	nbr = va_arg(*ap, long double);
	flag->sign = (nbr >= 0) ? 1 : -1;
	bits = ((char *)&nbr);
	if ((flag->len = create_l_doub(bits, mant)) < 0)
		return (handle_exept(flag, flag->len, nbr >= 0));
	while (mant[flag->len] && mant[flag->len] != '.')
		flag->len++;
	flag->len += fill_att(flag, nbr, att);
	flag->len = flag->width - (flag->preci + flag->len + 1);
	if (!(espaces = make_espaces(flag, flag->len)))
		return (-1);
	flag->len = print_double(flag, mant, espaces, att);
	free(espaces);
	return (flag->len);
}

int	get_ull_int(t_flags *flag, va_list *ap)
{
	unsigned long long int nbr;

	flag->plus = 0;
	flag->space = 0;
	nbr = va_arg(*ap, unsigned long long int);
	if (flag->conv == 'u' || flag->conv == 'D')
		return (print_unb(flag, nbr, 10));
	if (flag->conv == 'U')
		return (print_unb(flag, nbr, 10));
	if (flag->conv == 'o' || flag->conv == 'O')
		return (print_unb(flag, nbr, 8));
	if (flag->conv == 'x' || flag->conv == 'X')
		return (print_unb(flag, nbr, 16));
	return (-1);
}

int	get_ul_int(t_flags *flag, va_list *ap)
{
	unsigned long int nbr;

	flag->plus = 0;
	flag->space = 0;
	nbr = va_arg(*ap, unsigned long int);
	if (flag->conv == 'u' || flag->conv == 'D' || flag->conv == 'U')
		return (print_unb(flag, nbr, 10));
	if (flag->conv == 'o' || flag->conv == 'O')
		return (print_unb(flag, nbr, 8));
	if (flag->conv == 'x' || flag->conv == 'X')
		return (print_unb(flag, nbr, 16));
	return (-1);
}
