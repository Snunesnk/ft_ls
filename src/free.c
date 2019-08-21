/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:00:18 by snunes            #+#    #+#             */
/*   Updated: 2019/08/21 15:35:59 by snunes           ###   ########.fr       */
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
	free(tree->owner);
	free(tree->group);
	free(tree->mtime);
	if (tree->right)
		free_tree(tree->right);
	free(tree);
	tree = NULL;
}
