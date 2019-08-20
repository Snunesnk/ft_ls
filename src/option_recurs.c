/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_recurs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:39:35 by snunes            #+#    #+#             */
/*   Updated: 2019/08/20 19:12:29 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		requi(t_length *len, char *root, int mode)
{
	char	*name;

	name = extract_name(root);
	if ((ft_strequ(name, ".\0") || ft_strequ(name, "..\0")) && !mode)
	{
		if (len->option & 64)
			return (1);
		free(name);
		return (0);
	}
	if (name[0] != '.')
	{
		free(name);
		return (1);
	}
	if (name[0] == '.' && len->option & 8)
	{
		free(name);
		return (1);
	}
	free(name);
	return (0);
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
	if (len->option & 64)
		print_dir(tree, len, 3);
	return (tree);
}

void	print_dir(t_node *tree, t_length *len, int mode)
{
	if (mode && mode != 3)
	{
		if (!(len->option & 4))
			ft_printf("\n\0");
		ft_printf("\n\0");
		ft_printf("%s:\n", tree->name);
	}
	if (!mode || (mode == 3 && (len->option & 4) && tree->type == 4))
		ft_printf("total %d\n", len->blocks);
}

void	print_recurs(t_node *tree, t_length *len)
{
	t_node		*directory;
	t_length	*new_len;

	new_len = NULL;
	directory = NULL;
	if (!tree)
		return ;
	if (tree->left && ft_printf("a gauche\n"))
		print_recurs(tree->left, len);
	if (tree->type == 4 && requi(len, tree->name, 0))
	{
		ft_printf("tree->name: %s\n", tree->name);
		if (!(new_len = init_len(len)))
			return ;
		ft_printf("ca va print des infos\n");
		print_dir(tree, new_len, 1);
		ft_printf("ca va faire la recurs\n");
		directory = recurs(directory, tree->name, new_len);
		if (directory)
			print_tree(directory, new_len);
		free(new_len);
		if ((tree->links > 2 || (len->option & 8)) && ft_printf("ca va aller dans un fichier\n"))
			print_recurs(directory, len);
	}
	if (tree->right && ft_printf("virage a droite\n"))
		print_recurs(tree->right, len);
	//free_node(directory);
	ft_printf("sortie\n");
}
