/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:17:45 by snunes            #+#    #+#             */
/*   Updated: 2019/08/06 18:39:18 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_

t_node	*init_node(t_node *node, char *name)
{
	struct stat st;

	if (!(node->name = ft_strdup(name)))
		return (NULL);
	stat(ft_strjoin((char *)singleton(1), name), &st);
	node->length = ft_strlen(name);
	if (files->d_type == 8
			&& (st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) / 64 == 7)
		new_node->type = 7;
	else
		new_node->type = files->d_type;
	lstat(path, &st);
	fill_spec(st, new_node);
	new_node->right = NULL;
	new_node->left = NULL;

}

t_node	*creat_new_node(t_node *tree, char *file)
{
	t_node	*new_node;

	if (!(new_node = init_node(new_node, file)))
		return (0);
}
