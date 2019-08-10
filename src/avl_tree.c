/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 16:46:53 by snunes            #+#    #+#             */
/*   Updated: 2019/08/10 17:51:47 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	heigth(t_node *node)
{
	if (node == NULL)
		return (0);
	return (node->heigth);
}

int	check_balance(t_node *node)
{
	if (!node)
		return (0);
	return (heigth(node->left) - heigth(node->right));
}

t_node	*right_rotate(t_node *node)
{
	t_node *x;
	t_node *y;

	x = node->left;
	y = x->right;
	x->right = node;
	node->left = y;
	node->heigth = MAX(heigth(node->left), heigth(node->right)) + 1;
	x->heigth = MAX(heigth(x->left), heigth(x->right)) + 1;
	return (x);
}

t_node	*left_rotate(t_node *node)
{
	t_node *x;
	t_node *y;

	x = node->right;
	y = x->left;
	x->left = node;
	node->right = y;
	node->heigth = MAX(heigth(node->left), heigth(node->right)) + 1;
	x->heigth = MAX(heigth(x->left), heigth(x->right)) + 1;
	return (x);
}

t_node	*balance(int balanced, t_node *node, t_node *new_node, int mode)
{
	if (balanced > 1 && ft_node_cmp(node, new_node, mode) <= 0)
		return (right_rotate(node));
	if (balanced < -1 && ft_node_cmp(node, new_node, mode) > 0)
		return (left_rotate(node));
	if (balanced > 1 && ft_node_cmp(node, new_node, mode) > 0)
	{
		node->left = left_rotate(node);
		return (right_rotate(node));
	}
	if (balanced < -1 && ft_node_cmp(node, new_node, mode) <= 0)
	{
		node->right = right_rotate(node);
		return (left_rotate(node));
	}
	return (node);
}
