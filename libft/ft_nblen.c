/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nblen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:38:19 by snunes            #+#    #+#             */
/*   Updated: 2019/07/23 12:04:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nblen(__uintmax_t nbr, unsigned int base)
{
	int pow;

	pow = 1;
	if (nbr == 0)
		return (1);
	while (nbr >= base)
	{
		pow += 1;
		nbr /= base;
	}
	return (pow);
}
