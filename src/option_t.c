/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_t.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:55:02 by snunes            #+#    #+#             */
/*   Updated: 2019/08/15 18:26:18 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_buff(char *buff[13])
{
	buff[0] = "Jan\0"
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

int		cmp_month(char *node_month, char *tree_month)
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
	return (result - i);
}

int		cmp_hour(char *node->time, char *tree->time)
{

}

int		ft_tmpcmp(char *node_time, char *tree_time)
{
	int result;

	if ((result = ft_atoi(node_time + 20) - ft_atoi(tree_time + 20)))
		return (result);
	if ((result = cmp_month(node_time + 4, tree_time + 4)))
		return (result);
	node_time[11] = '\0';
	tree_time[11] = '\0';
	if ((result = ft_atoi(node_time + 8) - ft_atoi(tree_time + 8)))
		return (result);
	node_time[20] = '\0';
	tree_time[20] = '\0';
	if (result = cmp_hour(node_time + 12, tree_time + 12))
		return (result);
	return (0);
}
