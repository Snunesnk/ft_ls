/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 11:13:08 by snunes            #+#    #+#             */
/*   Updated: 2019/08/15 12:48:02 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		depth_calc(char *path)
{
	int depth;
	int i;

	depth = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			depth++;
		i++;
	}
	return (depth);
}

int		path_cmp(char *path1, char *path2)
{
	int	i;
	int	depth1;
	int	depth2;

	i = 0;
	depth1 = depth_calc(path1);
	depth2 = depth_calc(path2);
	while (path1[i] && path2[i] && path1[i] == path2[i])
	{
		if (path1[i] == '/')
			depth1--;
		if (path2[i] == '/')
			depth2--;
		i++;
	}
	if ((depth1 == 0 && depth2) > 0 || (path1[0] == '/' && path2[0] != '/'))
		return (-1);
	else if ((depth1 && depth2) || (!depth1 && !depth2))
		return (0);
	return (1);
}

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
	int 	i;
	int 	j;
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

t_node *add_content(t_node *tree, char *name, t_length *len)
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
	}
	else
	{
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
	}
	closedir(directory);
	free(root);
	return (tree);
}
