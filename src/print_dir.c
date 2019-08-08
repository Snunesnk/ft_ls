/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 11:13:08 by snunes            #+#    #+#             */
/*   Updated: 2019/08/08 18:22:25 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_recurs(t_node *tree, int *option)
{
	DIR		*test;
	char	**path;

	if (!tree)
		return ;
	if (tree->left)
		print_recurs(tree->left, option);
	path = sing_path(tree->name);
	if ((tree->name[0] != '.' || *option & 8))
	{
		if (!ft_strequ(tree->name, ".\0") && !ft_strequ(tree->name, "..\0")
				&& (test = opendir(*path)))
		{
			ft_printf("\n\n./%s:\n", *path);
			print_files(test, path);
		}
	}
	sing_path("\0");
	if (tree->right)
		print_recurs(tree->right, option);
}

void	print_files(DIR *directory, char **path)
{
	t_node			*tree;
	struct dirent	*files;
	int				*option;
	DIR				*dir2;
	t_length		*len;
	char			*str;

	str = ft_strdup(*path);
	option = (int *)singleton(2);
	len = (t_length *)singleton(3);
	tree = NULL;
	while ((files = readdir(directory)))
	{
		dir2 = opendir(str);
		tree = add_node(tree, files->d_name, dir2, 2);
		closedir(dir2);
	}
	if (*option & 4)
		ft_printf("total %d\n", len->blocks);
	print_tree(tree, 2);
	if (*option & 16)
		print_recurs(tree, option);
}
