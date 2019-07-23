/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:41:14 by snunes            #+#    #+#             */
/*   Updated: 2019/07/23 12:03:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_uhh_int(t_flags *flag, va_list *ap)
{
	unsigned char nbr;

	nbr = va_arg(*ap, int);
	if (flag->conv == 'u' || flag->conv == 'U')
		return (print_unb(flag, nbr, 10));
	if (flag->conv == 'o' || flag->conv == 'O')
		return (print_unb(flag, nbr, 8));
	if (flag->conv == 'x' || flag->conv == 'X')
		return (print_unb(flag, nbr, 16));
	return (-1);
}

int	get_uh_int(t_flags *flag, va_list *ap)
{
	unsigned short int nbr;

	flag->plus = 0;
	flag->space = 0;
	nbr = va_arg(*ap, int);
	if (flag->conv == 'u' || flag->conv == 'U')
		return (print_unb(flag, nbr, 10));
	if (flag->conv == 'o' || flag->conv == 'O')
		return (print_unb(flag, nbr, 8));
	if (flag->conv == 'x' || flag->conv == 'X')
		return (print_unb(flag, nbr, 16));
	return (-1);
}

int	get_uj_int(t_flags *flag, va_list *ap)
{
	__uintmax_t nbr;

	flag->plus = 0;
	flag->space = 0;
	nbr = va_arg(*ap, __uintmax_t);
	if (flag->conv == 'u' || flag->conv == 'U')
		return (print_unb(flag, nbr, 10));
	if (flag->conv == 'o' || flag->conv == 'O')
		return (print_unb(flag, nbr, 8));
	if (flag->conv == 'x' || flag->conv == 'X')
		return (print_unb(flag, nbr, 16));
	return (-1);
}

int	get_j_int(t_flags *flag, va_list *ap)
{
	__intmax_t nbr;

	nbr = va_arg(*ap, __intmax_t);
	if (flag->conv == 'd' || flag->conv == 'i' || flag->conv == 'D')
		return (print_nb(flag, nbr, 10));
	if (flag->conv == 'u' || flag->conv == 'U')
		return (print_unb(flag, nbr, 10));
	if (flag->conv == 'o' || flag->conv == 'O')
		return (print_unb(flag, nbr, 8));
	if (flag->conv == 'x' || flag->conv == 'X')
		return (print_unb(flag, nbr, 16));
	return (-1);
}
