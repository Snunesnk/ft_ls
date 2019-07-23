/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrange_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 11:42:00 by snunes            #+#    #+#             */
/*   Updated: 2019/06/28 11:47:58 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_reset_flags(t_flags *flag, int nb_flags)
{
	flag->nb = 0;
	flag->len = 0;
	flag->diez = 0;
	flag->plus = 0;
	flag->space = 0;
	flag->minus = 0;
	flag->zero = 0;
	flag->width = 0;
	flag->preci = -1;
	flag->conv = 0;
	flag->sign = 0;
	flag->color = 0;
	if (nb_flags > 0)
		flag->spos = 0;
}

void	order_flags(t_flags *flag)
{
	if (flag->width < 0)
	{
		flag->minus = 1;
		flag->width = -flag->width;
	}
	if (flag->preci < 0)
		flag->preci = -1;
	if (flag->plus == 1)
		flag->space = 0;
	if (flag->minus == 1)
		flag->zero = 0;
	if (flag->preci > -1 && flag->conv != 'L' && flag->conv != 'f')
		flag->zero = 0;
}
