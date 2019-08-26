/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_t.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:55:02 by snunes            #+#    #+#             */
/*   Updated: 2019/08/26 12:49:29 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		init_buff(char *buff[13])
{
	buff[0] = "Jan\0";
	buff[1] = "Feb\0";
	buff[2] = "Mar\0";
	buff[3] = "Apr\0";
	buff[4] = "May\0";
	buff[5] = "Jun\0";
	buff[6] = "Jul\0";
	buff[7] = "Aug\0";
	buff[8] = "Sep\0";
	buff[9] = "Oct\0";
	buff[10] = "Nov\0";
	buff[11] = "Dec\0";
	buff[12] = "\0";
}

int			cmp_month(char *node_month, char *tree_month)
{
	char	*buff[13];
	int		i;
	int		result;

	i = 0;
	init_buff(buff);
	node_month[3] = '\0';
	tree_month[3] = '\0';
	while (!ft_strequ(node_month, buff[i]) && buff[i])
		i++;
	result = i;
	i = 0;
	while (!ft_strequ(tree_month, buff[i]) && buff[i])
		i++;
	node_month[3] = ' ';
	tree_month[3] = ' ';
	return (i - result);
}

int			ft_tmpcmp(char *node_time, char *tree_time)
{
	int result;

	result = 0;
	if ((result = ft_atoi(tree_time + 16) - ft_atoi(node_time + 16)))
		return (result);
	if ((result = cmp_month(node_time, tree_time)))
		return (result);
	node_time[15] = '\0';
	tree_time[15] = '\0';
	result = ft_strcmp(tree_time + 4, node_time + 4);
	node_time[15] = ' ';
	tree_time[15] = ' ';
	return (result);
}

long int	calc_time(char *time)
{
	long int	seconds;
	int			i;
	char		*jan;

	seconds = 0;
	jan = ft_strdup("Jan\0");
	i = cmp_month(time, jan) * -1;
	seconds += 86400 * 30 * i + ((i - 1) / 2) * 86400;
	if (i >= 2)
		seconds -= 86400;
	free(jan);
	seconds += (ft_atoi(time + 16) - 1970) * 31536000;
	seconds += ((ft_atoi(time + 16) - 1969) / 4) * 86400 - 86400;
	time[6] = '\0';
	time[9] = '\0';
	time[12] = '\0';
	time[15] = '\0';
	seconds += ft_atoi(time + 4) * 86400;
	seconds += ft_atoi(time + 7) * 3600 + ft_atoi(time + 10) * 60 - 7200;
	seconds += ft_atoi(time + 13);
	time[6] = ' ';
	time[9] = ':';
	time[12] = ':';
	time[15] = ' ';
	return (seconds);
}

void		print_time(char *node_time)
{
	time_t		seconds;
	long int	node_sec;

	seconds = time(NULL);
	node_sec = calc_time(node_time);
	if (seconds - node_sec > 30 * 86400 * 6 + 3 * 86400 || node_sec > seconds)
	{
		if (node_time[20])
			ft_memmove(node_time + 8, node_time + 16, 5);
		else
			ft_memmove(node_time + 8, node_time + 16, 4);
		node_time[7] = ' ';
	}
	node_time[12] = (node_time[12] == ':') ? '\0' : node_time[12];
	ft_printf(" %.*s ", 13, node_time);
}
