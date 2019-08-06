/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:21:31 by snunes            #+#    #+#             */
/*   Updated: 2019/08/06 16:16:54 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	up_a_dir(char *path)
{
	int i;
	int count;

	count = 0;
	i = ft_strlen(path);
	while (path && i >= 0 && count != 2)
	{
		i--;
		if (path[i] == '/')
			count++;
	}
	if (count == 2)
		path[i + 1] = '\0';
}

int	print_recurs(t_node *tree, t_opt *options)
{
	t_length len;

	if (!tree)
		return (0);
	if (tree->left)
		print_recurs(tree->left, options);
	if ((tree->name[0] != '.' || options->opt & 8))
	{
		if (!ft_strequ(tree->name, ".\0") && !ft_strequ(tree->name, "..\0")
				&& tree->type == 4)
		{
			read_all(tree, tree->name, options, &len);
			up_a_dir(options->path);
		}
	}
	if (tree->right)
		print_recurs(tree->right, options);
	return (1);
}
