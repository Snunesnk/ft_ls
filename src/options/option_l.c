/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:10:13 by snunes            #+#    #+#             */
/*   Updated: 2019/09/02 12:44:35 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_perm(t_node *node, struct stat st)
{
	node->sp_bit = ((st.st_mode) / 512) % 8;
	node->u_perm = (st.st_mode & S_IRWXU) / 64;
	node->g_perm = (st.st_mode & S_IRWXG) % 64 / 8;
	node->o_perm = (st.st_mode & S_IRWXO) % 8;
	node->type -= (node->type == 8 && IS_EXEC(node->o_perm)) ? 1 : 0;
}

void	update_l_next(t_node *node, t_length *len)
{
	if ((node->name[0] != '.' || len->option & 8))
		len->blocks += node->blocks;
	if (node->major == -1)
		return ;
	if (ft_nbrlen(node->major) + 3 > len->major
					&& (node->name[0] != '.' || len->option & 8))
		len->major = ft_nbrlen(node->major) + 3;
}

void	update_l(t_node *node, t_length *len)
{
	struct winsize	size;

	if (((len->option & 64) && node->type == 4))
		return ;
	ioctl(0, TIOCGWINSZ, &size);
	len->column = size.ws_col;
	if (ft_strlen(node->name) + 1 > (size_t)len->name_l
			&& (node->name[0] != '.' || len->option & 8))
		len->name_l = ft_strlen(node->name) + 1;
	if (!(len->option & 256))
		return ;
	if (ft_nbrlen(node->links) + 2 > len->link_l
					&& (node->name[0] != '.' || len->option & 8))
		len->link_l = ft_nbrlen(node->links) + 2;
	if (ft_strlen(node->owner) + 2 > (size_t)len->user_l
					&& (node->name[0] != '.' || len->option & 8))
		len->user_l = ft_strlen(node->owner) + 1;
	if (ft_strlen(node->group) > (size_t)len->group_l
					&& (node->name[0] != '.' || len->option & 8))
		len->group_l = ft_strlen(node->group);
	if (ft_nbrlen(node->size) + 2 > len->size_l
					&& (node->name[0] != '.' || len->option & 8))
		len->size_l = ft_nbrlen(node->size) + 2;
	update_l_next(node, len);
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

int		print_link(t_node *tree)
{
	char	buff[500];
	size_t	size;

	if (!(size = readlink(tree->path, buff, 500)))
		return (0);
	buff[size] = '\0';
	ft_printf(" -> %s", buff);
	return (1);
}
