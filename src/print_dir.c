/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 11:13:08 by snunes            #+#    #+#             */
/*   Updated: 2019/08/12 13:54:43 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_recurs(t_node *tree, int **option)
{
	DIR		*test;
	char	**path;
	int		errno;

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
	/*		if (*path[0] != '/')
				ft_printf("./");*/
			ft_printf("%s:\n", *path);
			print_files(tree, test, path);
			closedir(test);
		}
	}
	sing_path("\0");
	if (tree->right)
		print_recurs(tree->right, option);
}

void	print_files(t_node *tree, DIR *directory, char **path)
{
	struct dirent	*files;
	int				**option;
	t_length		**len;
	char			*str;

	str = ft_strdup(*path);
	option = (int **)singleton(2);
	len = (t_length **)singleton(3);
	ft_printf("tree->name = %s, path = %s\n", tree->name, *path);
	while ((files = readdir(directory)) && ft_printf("fichier act = %s\n", files->d_name))
		tree = add_node(tree, files, 2, *path);
	if ((**option & 4) && tree)
		ft_printf("total %d\n", (*len)->blocks);
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
	file[j - i] = '\0';
	if (i < 0)
		return (".\0");
	return (root);
}
