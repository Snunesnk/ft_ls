/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlongnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 05:13:15 by snunes            #+#    #+#             */
/*   Updated: 2019/06/05 05:23:01 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlongnbr(long long int nbr)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		if (nbr == -9223372036854775807)
		{
			ft_putchar('9');
			ft_putlongnbr(223372036854775808);
		}
		else
			ft_putlongnbr(-nbr);
	}
	else
	{
		if (nbr < 10)
			ft_putchar(nbr + 48);
		else
		{
			ft_putlongnbr(nbr / 10);
			ft_putchar((nbr % 10) + 48);
		}
	}
}
