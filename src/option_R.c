/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:33:19 by snunes            #+#    #+#             */
/*   Updated: 2019/08/15 17:24:12 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node	*recurs(t_node *tree, char *path, t_length *len)
{
	DIR				*dir;
	struct dirent	*file;

	file = NULL;
	if(!(dir = opendir(path)))
		return ((t_node *)ft_error(extract_name(path)));
	while ((file = readdir(dir)))
		tree = add_node(tree, file, path, len);
	closedir(dir);
	return (tree);
}
