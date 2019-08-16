/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:33:19 by snunes            #+#    #+#             */
/*   Updated: 2019/08/16 14:29:35 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node	*recurs(t_node *tree, char *path, t_length *len)
{
	DIR				*dir;
	struct dirent	*file;
	char			*name;

	name = NULL;
	file = NULL;
	if(!(dir = opendir(path)))
		return ((t_node *)ft_error(extract_name(path)));
	while ((file = readdir(dir)))
	{
		name = ft_strjoin(path, "/\0");
		name = ft_strjoin_free(&name, file->d_name, 1);
		if (requi(len, name, 1))
		{
			if (!(tree = add_node(tree, file, path, len)))
				return (NULL);
		}
		free(name);
		name = NULL;
	}
	closedir(dir);
	print_dir(tree, len, 0);
	return (tree);
}

void	print_dir(t_node *tree, t_length *len, int mode)
{
	if (mode)
	{
		ft_printf("\n\0");
		ft_printf("%s:\n", tree->name);
	}
	if (!mode)
		ft_printf("total %d\n", len->blocks);
}

void	print_recurs(t_node *tree, t_length *len)
{
	t_node		*directory;
	t_length	*new_len;

	new_len = NULL;
	directory = NULL;
	if (!tree)
		return;
	if (tree->left)
		print_recurs(tree->left, len);
	if (tree->type == 4 && requi(len, tree->name, 0))
	{
		if (!(new_len = init_len(len)))
			return ;
		print_dir(tree, new_len, 1);
		directory = recurs(directory, tree->name, new_len);
		if (directory)
			print_tree(directory, new_len);
		free(new_len);
		if (tree->links > 2 || (len->option & 8))
			print_recurs(directory, len);
	}
	if (tree->right)
		print_recurs(tree->right, len);
	free_node(tree);
}
