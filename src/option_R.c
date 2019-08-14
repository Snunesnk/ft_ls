/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:33:19 by snunes            #+#    #+#             */
/*   Updated: 2019/08/14 16:41:19 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node	*recurs(t_node *tree, char *path, t_length *len)
{
	DIR				*dir;
	struct dirent	*file;

//	ft_printf("entree recurs\n");
	file = NULL;
	dir = opendir(path);
	while ((file = readdir(dir)))
		tree = add_node(tree, file, path, len);
	closedir(dir);
//	ft_printf("sortie recurs\n");
	return (tree);
}
