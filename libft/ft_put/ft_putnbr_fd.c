/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:49:49 by snunes            #+#    #+#             */
/*   Updated: 2019/04/10 13:13:22 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			ft_putnbr_fd(147483648, fd);
		}
		else
			ft_putnbr_fd(-n, fd);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd((n + 48), fd);
		else
		{
			ft_putnbr_fd((n / 10), fd);
			ft_putchar_fd((n % 10 + 48), fd);
		}
	}
}
