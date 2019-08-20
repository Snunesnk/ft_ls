/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:10:13 by snunes            #+#    #+#             */
/*   Updated: 2019/08/20 19:04:58 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	update_l(t_node *node, t_length *len)
{
	char			*name;
	struct	winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	len->column = size.ws_col;
	if (len->option & 64)
		name = ft_strdup(node->name);
	else
		name = extract_name(node->name);
	if (ft_strlen(name) + 1 > (size_t)len->name_l
			&& (name[0] != '.' || len->option & 8))
		len->name_l = ft_strlen(name) + 1;
	if (ft_nbrlen(node->links) + 2 > len->link_l
					&& (name[0] != '.' || len->option & 8))
		len->link_l = ft_nbrlen(node->links) + 2;
	if (ft_strlen(node->owner) + 1 > (size_t)len->user_l
					&& (name[0] != '.' || len->option & 8))
		len->user_l = ft_strlen(node->owner);
	if (ft_strlen(node->group) > (size_t)len->group_l
					&& (name[0] != '.' || len->option & 8))
		len->group_l = ft_strlen(node->group);
	if (ft_nbrlen(node->size) + 2 > len->size_l
					&& (name[0] != '.' || len->option & 8))
		len->size_l = ft_nbrlen(node->size) + 2;
	if ((name[0] != '.' || len->option & 8))
		len->blocks += node->blocks;
	free(name);
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

int		print_link(t_node *tree)
{
	char	buff[500];
	size_t	size;

	if (!(size = readlink(tree->name, buff, 500)))
		return ((int)ft_error(extract_name(tree->name)));
	buff[size] = '\0';
	ft_printf(" -> %s", buff);
	return (1);
}
