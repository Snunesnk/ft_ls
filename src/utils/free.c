/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:00:18 by snunes            #+#    #+#             */
/*   Updated: 2019/09/06 13:15:14 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_tree(t_node *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		free_tree(tree->left);
	free(tree->name);
	free(tree->path);
	if (tree->owner)
		free(tree->owner);
	if (tree->group)
		free(tree->group);
	if (tree->mtime)
		free(tree->mtime);
	if (tree->right)
		free_tree(tree->right);
	free(tree);
	tree = NULL;
}

int		free_len(t_length *len)
{
	if (len)
		free(len);
	return (1);
}
