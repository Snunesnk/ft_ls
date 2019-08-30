/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 14:27:38 by snunes            #+#    #+#             */
/*   Updated: 2019/08/30 15:04:26 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node	*add_content(t_node *tree, char *path, t_length *len)
{
	DIR				*directory;
	char			*name;
	struct dirent	*file;
	char			*root;

	if (!(root = find_root(path)))
		return (NULL);
	directory = opendir(root);
	if (!directory)
		return (add_error(tree, path, strerror(errno), len));
	if (!(name = (ft_strequ(root, ".")) ? ft_strdup(path) : extract_name(path)))
		return (NULL);
	file = readdir(directory);
	while (file && !ft_filequ(name, file->d_name))
		file = readdir(directory);
	if (!file && !(opendir(path)))
		return (add_error(tree, path, strerror(errno), len));
	if (!(tree = add_node(tree, file, path, len)))
		return (NULL);
	free(name);
	free(root);
	closedir(directory);
	return (tree);
}

void	print_content(t_node *tree, t_length *len)
{
	t_node		*new_tree;
	t_length	*new_len;

	len->option |= 1024;
	new_tree = NULL;
	print_dir(tree, len, 1);
	if (!(new_len = init_len(len)))
		return ;
	if (!(new_tree = recurs(new_tree, tree->path, new_len)))
		return ;
	print_tree(new_tree, new_len);
	if (!(len->option & 4))
		ft_printf("\n");
	free_tree(new_tree);
	free(new_len);
}

void	print_first(t_node *tree, t_length *len)
{
	if (!tree)
		return ;
	if (tree->left && (tree->left->type != 4 || !(len->option & 16)))
		print_first(tree->left, len);
	if (tree->type == 4 && (len->option & 16))
		return ;
	else if (tree->type == 4)
	{
		print_content(tree, len);
		if (tree->right && (tree->right->type != 4 || !(len->option & 16)))
			print_first(tree->right, len);
		return ;
	}
	if (len->option & 256 && tree->type != 20)
		print_info(tree, len);
	if (!(len->option & 4) && len->written + len->name_l > len->column)
		len->written = (tree->type == 20) ? 0 : write(1, "\n", 1) - 1;
	print_name(tree, len);
	len->written += len->name_l;
	if ((len->option & 256) && tree->type == 10)
		print_link(tree);
	while (len->name_l > tree->length++ && !(len->option & 4))
		write(1, " ", 1);
	if (len->option & 4 || tree->type == 20)
		write(1, "\n", 1);
	len->option += (len->option & 128 || tree->type == 20) ? 0 : 128;
	if (tree->right && (tree->right->type != 4 || !(len->option & 16)))
		print_first(tree->right, len);
}

