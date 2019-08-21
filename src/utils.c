/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 11:13:08 by snunes            #+#    #+#             */
/*   Updated: 2019/08/21 15:51:40 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*extract_name(char *path)
{
	char	*name;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == '/' && path[i + 1])
			j = i + 1;
		i++;
	}
	i = (path[i] == '/') ? i - 1 : i;
	if (!(name = (char *)ft_memalloc(sizeof(char) * (i - j + 1))))
		return (NULL);
	i = 0;
	while (path[j] && path[j] != '/')
	{
		name[i] = path[j];
		i++;
		j++;
	}
	name[i] = '\0';
	return (name);
}

char	*find_root(char *file)
{
	int		i;
	int		j;
	char	*root;

	if (!(root = ft_strdup(file)))
		return (NULL);
	i = 0;
	j = -1;
	while (root[i] && i + 1 < (int)ft_strlen(root))
	{
		if (root[i] == '/')
			j = i + 1;
		i++;
	}
	if (j > 0)
		root[j] = '\0';
	if (j == -1)
	{
		root[0] = '.';
		root[1] = '/';
		root[2] = 0;
	}
	return (root);
}

t_node	*add_content(t_node *tree, char *path, t_length *len)
{
	DIR				*directory;
	char			*root;
	char			*name;
	struct dirent	*file;

	root = NULL;
	if (!(root = find_root(path)))
		return ((t_node *)ft_error(ft_strdup(name)));
	if (!(directory = opendir(root)))
		return ((t_node *)ft_error(root));
	if (!(name = extract_name(path)))
		return ((t_node *)ft_error(ft_strdup(name)));
	file = readdir(directory);
	while (file && !ft_strequ(name, file->d_name))
		file = readdir(directory);
	if (!file)
		return ((t_node *)ft_error(ft_strjoin_free(&root, name, 3)));
	if (file && !(tree = add_node(tree, file, root, len)))
		return ((t_node *)ft_error(ft_strjoin_free(&root, name, 3)));
	free(root);
	free(name);
	closedir(directory);
	return (tree);
}

void	print_content(t_node *tree, t_length *len)
{
	t_node		*new_tree;
	t_length	*new_len;

	new_tree = NULL;
	if (!(new_len = init_len(len)))
		return ;
	print_dir(tree, new_len, 1);
	if (!(new_tree = recurs(new_tree, tree->name, new_len)))
		return ;
	print_tree(new_tree, new_len);
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
	if (len->option & 4)
		print_info(tree, len);
	if (!(len->option & 4) && len->written + len->name_l > len->column)
		len->written = write(1, "\n", 1) - 1;
	print_name(tree, len);
	len->written += len->name_l;
	if ((len->option & 4) && tree->type == 10)
		print_link(tree);
	while (len->name_l > tree->length++ && !(len->option & 4))
		write(1, " ", 1);
	if (len->option & 4)
		write(1, "\n", 1);
	if (tree->right && (tree->right->type != 4 || !(len->option & 16)))
		print_first(tree->right, len);
}
