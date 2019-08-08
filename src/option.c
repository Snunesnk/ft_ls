/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:10:13 by snunes            #+#    #+#             */
/*   Updated: 2019/08/08 15:48:17 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	update_l(t_node *node)
{
	int			*option;
	t_length	*len;

	len = (t_length *)singleton(3);
	option = (int *)singleton(2);
	if (ft_strlen(node->name) + 1 > (size_t)len->name_l
			&& (node->name[0] != '.' || *option & 8))
			len->name_l = ft_strlen(node->name) + 1;
	if (ft_nbrlen(node->links) + 2 > len->link_l
					&& (node->name[0] != '.' || *option & 8))
			len->link_l = ft_nbrlen(node->links) + 2;
	if (ft_strlen(node->owner) + 1 > (size_t)len->user_l
					&& (node->name[0] != '.' || *option & 8))
			len->user_l = ft_strlen(node->owner) + 1;
	if (ft_strlen(node->group) + 2 > (size_t)len->group_l
					&& (node->name[0] != '.' || *option & 8))
			len->group_l = ft_strlen(node->group) + 2;
	if (ft_nbrlen(node->size) + 2 > len->size_l
					&& (node->name[0] != '.' || *option & 8))
			len->size_l = ft_nbrlen(node->size) + 2;
	if ((node->name[0] != '.' || *option & 8))
			len->blocks += node->blocks;
}

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

int		is_writeable(int perm)
{
	return ((perm == 7 || perm == 6 || perm == 3 || perm == 2));
}

char	*give_time(struct stat st)
{
	char	*ltime;

	ltime = ctime(&st.st_mtimespec.tv_sec);
	ft_memmove(ltime, ltime + 4, 26);
	ltime[12] = '\0';
	return (ltime);
}
