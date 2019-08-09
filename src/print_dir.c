/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 11:13:08 by snunes            #+#    #+#             */
/*   Updated: 2019/08/09 16:50:10 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_recurs(t_node *tree, int **option)
{
	DIR		*test;
	char	**path;

	if (!tree)
		return ;
	if (tree->left)
		print_recurs(tree->left, option);
	path = sing_path(tree->name);
	if ((tree->name[0] != '.' || **option & 8))
	{
		if (!ft_strequ(tree->name, ".\0") && !ft_strequ(tree->name, "..\0")
				&& (test = opendir(*path)))
		{
			if (((**option & 32) || (**option & 16)) && !(**option & 64))
				ft_printf("\n");
			if (*path[0] != '/')
				ft_printf("./");
			ft_printf("%s:\n", *path);
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
	int				**option;
	t_length		**len;
	char			*str;

	str = ft_strdup(*path);
	option = (int **)singleton(2);
	**option = **option ^ 64;
	len = (t_length **)singleton(3);
	tree = NULL;
	while ((files = readdir(directory)))
		tree = add_node(tree, files, 2, "\0");
	if (**option & 4)
		ft_printf("total %d\n", (*len)->blocks);
	ft_printf("path print dir = %s\n", *path);
	print_tree(tree, 2);
	*len = init_len(len);
	if (**option & 16)
		print_recurs(tree, option);
}

t_node	*start_tree(t_node *tree, char *root, char *to_find)
{
	DIR				*directory;
	struct dirent	*files;

	directory = opendir(root);
	files = readdir(directory);
	while ((!ft_strequ(files->d_name, to_find)) && !ft_strequ(root, to_find))
		files = readdir(directory);
	tree = add_node(tree, files, 1, root);
	return (tree);
}

char	*find_root(char *root, char *file)
{
	int i;
	int j;

	if (!(root = ft_strdup(file)))
		return (NULL);
	i = ft_strlen(root) - 1;
	j = i;
	while (i > 0 && file[i] == '/')
		file[i--] = '\0';
	while (i >= 0 && root[i] != '/')
		root[i--] = '\0';
	while (i >= 0 && file[i] != '/')
		i--;
	if (i > 0)
		ft_memmove(file, file + i + 1, j - i);
/*	if (ft_strequ(file, "/\0"))
		file[0] = '.';*/
	if (i < 0)
		return (".\0");
	return (root);
}
