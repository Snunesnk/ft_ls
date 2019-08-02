/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_names.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:33:50 by snunes            #+#    #+#             */
/*   Updated: 2019/08/02 16:50:53 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int	add_elem(t_node *new_node, struct dirent *files)
{
	if (!(new_node->name = ft_strdup(files->d_name)))
		return (0);
	new_node->type = files->d_type;
	new_node->right = NULL;
	new_node->left = NULL;
	return (1);
}

int	add_node(struct dirent *files, t_node *names)
{
	t_node	*new_node;

	if (!(new_node = (t_node *)ft_memalloc(sizeof(t_node))))
			return (0);
	if (!(add_elem(new_node, files)))
	{
		free(new_node);
		return (0);
	}
	while (names)
	{
		if (ft_strcmp(new_node->name, names->name) <= 0)
			names = names->left;
		else
			names = names->right;
	}
		ft_printf("name before= %s\n", names->name);
	names = new_node;
		ft_printf("name after = %s\n", names->name);
	return (1);
}

int		organize_names(t_node *names, DIR *directory)
{
	struct dirent	*files;
	t_node			*tmp_node;

	files = readdir(directory);
	if (!(add_elem(names, files)))
		return (0);
	while ((files = readdir(directory)))
	{
		tmp_node = names;
		add_node(files, tmp_node);
		ft_printf("et de un en plus!\n");
	}
	return (1);
}
