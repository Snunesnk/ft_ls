/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_t2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 12:30:44 by snunes            #+#    #+#             */
/*   Updated: 2019/08/26 12:41:13 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*adjust_time(char *time)
{
	if (time[20] == ' ')
	{
		ft_memmove(time + 20, time + 24, 5);
		time = ft_memmove(time, time + 4, 21);
		time[21] = '\0';
	}
	else
	{
		time = ft_memmove(time, time + 4, 20);
		time[20] = '\0';
	}
	return (time);
}
