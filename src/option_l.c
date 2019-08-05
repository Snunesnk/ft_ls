/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 16:37:42 by snunes            #+#    #+#             */
/*   Updated: 2019/08/05 12:49:15 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	init_file_type(char file_type[20])
{
	file_type[0] = 1;
	file_type[2] = 2;
	file_type[4] = 4;
	file_type[6] = 6;
	file_type[8] = 7;
	file_type[10] = 8;
	file_type[12] = 10;
	file_type[14] = 12;
	file_type[16] = 14;
	file_type[18] = 0;
	file_type[1] = 'p';
	file_type[3] = 'c';
	file_type[5] = 'd';
	file_type[7] = 'b';
	file_type[9] = '-';
	file_type[11] = '-';
	file_type[13] = 'l';
	file_type[15] = 's';
	file_type[17] = 0;
	file_type[19] = 0;
}

int		give_length(int length, int to_reach)
{
	while (length < to_reach)
		length++;
	return (length);
}

void	update_l(t_length *len, t_node *node, t_opt *options)
{
	if (ft_strlen(node->name) > (size_t)len->name_l
			&& (node->name[0] != '.' || options->opt_a == 1))
		len->name_l = ft_strlen(node->name) + 1;
	if (ft_nbrlen(node->links) > len->link_l
			&& (node->name[0] != '.' || options->opt_a == 1))
		len->link_l = ft_nbrlen(node->links) + 3;
	if (ft_strlen(node->owner) > (size_t)len->user_l
			&& (node->name[0] != '.' || options->opt_a == 1))
		len->user_l = ft_strlen(node->owner) + 1;
	if (ft_strlen(node->group) > (size_t)len->group_l
			&& (node->name[0] != '.' || options->opt_a == 1))
		len->group_l = ft_strlen(node->group) + 2;
	if (ft_nbrlen(node->size) > len->size_l
			&& (node->name[0] != '.' || options->opt_a == 1))
		len->size_l = ft_nbrlen(node->size) + 3;
}

//void	ft_print_next(t_node *names);

char	*give_time(struct stat st)
{
	char	*time;

	time = ctime(&st.st_mtimespec.tv_sec);
	ft_memmove(time, time + 4, 5);
	return (time);
}
