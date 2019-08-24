/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_recurs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:39:35 by snunes            #+#    #+#             */
/*   Updated: 2019/08/24 17:25:52 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*creat_path(char *root, char *dir)
{
	int		length;
	char	*path;

	length = ft_strlen(root) + ft_strlen(dir) + 2;
	if (!(path = ft_memalloc(sizeof(char) * length)))
		return (NULL);
	path = ft_strcat(path, root);
	path = ft_strcat(path, "/");
	path = ft_strcat(path, dir);
	return (path);
}

t_node	*recurs(t_node *tree, char *path, t_length *len)
{
	DIR				*dir;
	struct dirent	*file;
	char			*name;

	name = NULL;
	file = NULL;
	if (!(dir = opendir(path)))
		return ((t_node *)ft_error(ft_strdup(path)));
	while ((file = readdir(dir)))
	{
		if (!(name = creat_path(path, file->d_name)))
			return (NULL);
		if (requi(len, name, 1))
		{
			if (!(tree = add_node(tree, file, path, len)))
				return (NULL);
		}
		free(name);
		name = NULL;
	}
	closedir(dir);
	if (tree)
		print_dir(tree, len, 3);
	return (tree);
}

void	print_recurs(t_node *tree, t_length *len)
{
	t_node		*directory;
	t_length	*new_len;

	new_len = NULL;
	directory = NULL;
	if (!tree)
		return ;
	if (tree->left)
		print_recurs(tree->left, len);
	if (tree->type == 4 && requi(len, tree->name, 0))
	{
		print_dir(tree, len, 1);
		if (!(new_len = init_len(len)))
			return ;
		directory = recurs(directory, tree->name, new_len);
		if (directory)
		{
			print_tree(directory, new_len);
			if ((tree->links > 2 || (len->option & 8)))
				print_recurs(directory, new_len);
			free_tree(directory);
		}
		free(new_len);
	}
	if (tree->right)
		print_recurs(tree->right, len);
}
