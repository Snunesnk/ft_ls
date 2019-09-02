/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 11:31:41 by snunes            #+#    #+#             */
/*   Updated: 2019/08/30 14:48:56 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node	*add_error(t_node *tree, char *path, char *error, t_length *len)
{
	t_node	*node;

	if (!(node = (t_node *)ft_memalloc(sizeof(t_node))))
		return (node);
	node->path = ft_strdup(error);
	node->name = ft_strdup(path);
	if (node->name[0] == '.' && node->name[1] == '/')
	{
		node->name = ft_memmove(node->name, node->name + 2, sizeof(node->name));
		node->name[ft_strlen(node->name) - 2] = '\0';
	}
	node->type = 20;
	node->right = NULL;
	node->left = NULL;
	node->mtime = NULL;
	node->owner = NULL;
	node->group = NULL;
	node->heigth = 1;
	tree = place_node(tree, node, len);
	return (tree);
}
