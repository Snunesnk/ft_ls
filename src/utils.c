/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 11:13:08 by snunes            #+#    #+#             */
/*   Updated: 2019/08/17 14:03:55 by snunes           ###   ########.fr       */
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
		if (path[i] == '/')
			j = i + 1;
		i++;
	}
	if (!(name = (char *)ft_memalloc(sizeof(char) * (i - j + 1))))
		return (NULL);
	i = 0;
	while (path[j])
		name[i++] = path[j++];
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
	while (root[i])
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
		root[1] = 0;
	}
	return (root);
}

t_node	*add_file(t_node *tree, char *name, t_length *len)
{
	DIR				*directory;
	char			*root;
	struct dirent	*file;

	if (!(root = find_root(name)))
		return ((t_node *)ft_error(name));
	if (!(directory = opendir(root)))
		return ((t_node *)ft_error(root));
	if (!(name = extract_name(name)))
		return ((t_node *)ft_error(name));
	file = readdir(directory);
	while (file && !ft_strequ(name, file->d_name))
		file = readdir(directory);
	if (!file)
		return ((t_node *)ft_error(ft_strjoin_free(&root, name, 3)));
	if (file && !(tree = add_node(tree, file, root, len)))
		return ((t_node *)ft_error(ft_strjoin_free(&root, name, 3)));
	free(root);
	closedir(directory);
	return (tree);
}

t_node	*add_content(t_node *tree, char *name, t_length *len)
{
	DIR				*directory;
	char			*root;
	struct dirent	*file;

	root = NULL;
	if ((directory = opendir(name)))
	{
		len->multi += 1;
		if (!(root = ft_strdup(name)))
			return ((t_node *)ft_error(name));
		while ((file = readdir(directory)))
		{
			if (!(tree = add_node(tree, file, root, len)))
				return ((t_node *)ft_error(name));
		}
		free(root);
		closedir(directory);
	}
	else
	{
		if (!(tree = add_file(tree, name, len)))
			return (NULL);
	}
	return (tree);
}
