/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:31:35 by snunes            #+#    #+#             */
/*   Updated: 2019/08/19 17:21:08 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int sign;
	int result;
	int count;

	sign = 1;
	count = 0;
	result = 0;
	if (str[0] == '-' || str[0] == '+' || ft_isspace(str[0]))
	{
		while (ft_isspace(str[count]))
			count++;
		if (str[count] == '-')
		{
			sign = -1;
			count++;
		}
		else if (str[count] == '+')
			count++;
	}
	while (str[count] <= '9' && str[count] >= '0')
	{
		result = (result * 10) + (str[count] - 48);
		count++;
	}
	return (result * sign);
}
