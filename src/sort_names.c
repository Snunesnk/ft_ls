/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_names.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:33:50 by snunes            #+#    #+#             */
/*   Updated: 2019/08/03 11:45:44 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int	add_elem(t_node *new_node, struct dirent *files)
{
	if (!(new_node->name = ft_strdup(files->d_name)))
		return (0);
	new_node->length = ft_strlen(files->d_name);
	new_node->type = files->d_type;
	new_node->right = NULL;
	new_node->left = NULL;
	return (1);
}

int	add_node(struct dirent *files, t_node **names)
{
	t_node	*new_node;
	t_node	*tmp_node;
	t_node	*tmp_tree;

	tmp_tree = *names;
	if (!(new_node = (t_node *)ft_memalloc(sizeof(t_node))))
			return (0);
	if (!(add_elem(new_node, files)))
	{
		free(new_node);
		return (0);
	}
	while (tmp_tree)
	{
		tmp_node = tmp_tree;
		if (ft_strcmp(new_node->name, tmp_tree->name) <= 0)
		{
			tmp_tree = tmp_tree->left;
			if (!tmp_tree)
				tmp_node->left = new_node;
		}
		else
		{
			tmp_tree = tmp_tree->right;
			if (!tmp_tree)
				tmp_node->right = new_node;
		}
	}
	return (1);
}

int		organize_names(t_node *names, DIR *directory, t_opt *options)
{
	struct dirent	*files;
	size_t			name_l;

	files = readdir(directory);
	name_l = ft_strlen(files->d_name);
	if (!(add_elem(names, files)))
		return (0);
	while ((files = readdir(directory)))
	{
		if (ft_strlen(files->d_name) > name_l && (files->d_name[0] != '.'
					|| options->opt_a == 1))
			name_l = ft_strlen(files->d_name);
		add_node(files, &names);
	}
	return (name_l);
}
