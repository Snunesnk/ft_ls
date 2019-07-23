/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:54:25 by snunes            #+#    #+#             */
/*   Updated: 2019/06/05 05:13:01 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		if (n == -2147483648)
		{
			ft_putchar('2');
			ft_putnbr(147483648);
		}
		else
			ft_putnbr(-n);
	}
	else
	{
		if (n < 10)
			ft_putchar(n + 48);
		else
		{
			ft_putnbr(n / 10);
			ft_putchar((n % 10) + 48);
		}
	}
}
