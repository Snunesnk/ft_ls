/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:17:45 by snunes            #+#    #+#             */
/*   Updated: 2019/08/08 17:51:54 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	fill_spec(struct stat st, t_node *new_node)
{
	struct passwd	*user;
	struct group	*grp;

	if (!(user = getpwuid(st.st_uid)))
	{
		perror("getpwuid()");
		return (0);
	}
	if (!(grp = getgrgid(st.st_gid)))
	{
		perror("getgrid()");
		return (0);
	}
	new_node->sp_bit = ((st.st_mode) / 512) % 8;
	new_node->u_perm = (st.st_mode & S_IRWXU) / 64;
	new_node->g_perm = (st.st_mode & S_IRWXG) % 64 / 8;
	new_node->o_perm = (st.st_mode & S_IRWXO) % 8;
	new_node->owner = ft_strdup(user->pw_name);
	new_node->group = ft_strdup(grp->gr_name);
	new_node->links = st.st_nlink;
	new_node->size = st.st_size;
	new_node->blocks = st.st_blocks;
	if (!(new_node->mtime = ft_strdup(give_time(st))))
		return (0);
	update_l(new_node);
	return (1);
}

t_node	*init_node(t_node *node, DIR *directory)
{
	struct	stat	st;
	struct dirent	*files;
	char			**path;

	path = sing_path(node->name);
//	ft_printf("path = %s, name = %s\n", *path, node->name);
	files = readdir(directory);
	while (!ft_strequ(files->d_name, node->name))
		files = readdir(directory);
	stat(*path, &st);
	node->length = ft_strlen(node->name);
	if (files->d_type == 8
			&& (st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) / 64 == 7)
		node->type = 7;
	else
		node->type = files->d_type;
	lstat(*path, &st);
	fill_spec(st, node);
	node->right = NULL;
	node->left = NULL;
	path = sing_path("\0");
	return (node);
}

int		ft_node_cmp(t_node *tree, t_node *new_node, int mode)
{
	int	*option;

	option = (int *)singleton(2);
	if (mode == 1 && new_node->type == 4 && tree->type != 4)
		return (1);
	else if (mode == 1 && new_node->type != 4 && tree->type == 4)
		return (0);
	else if (*option & 2 && !(*option & 1))
		return (ft_strcmp(new_node->name, tree->name) <= 0);
	else if (!(*option & 1))
		return (ft_strcmp(new_node->name, tree->name));
	return (0);
}

t_node	*place_node(t_node *tree, t_node *new_node, int mode)
{
	if (!tree)
		return (new_node);
	if (ft_node_cmp(tree, new_node, mode) <= 0)
		tree->left = place_node(tree->left, new_node, mode);
	else
		tree->right =  place_node(tree->right, new_node, mode);
	return (tree);
}

t_node	*add_node(t_node *tree, char *file, DIR *directory, int mode)
{
	t_node	*new_node;
	int		i;
	DIR		*dir;

	if (!(new_node = (t_node *)ft_memalloc(sizeof(t_node))))
		return (NULL);
	if (!(new_node->name = ft_strdup(file)))
		return (NULL);
	i = ft_strlen(new_node->name) - 1;
	while (i >= 0 && new_node->name[i] == '/')
		new_node->name[i--] = '\0';
	if (mode == 1 && (dir = opendir(new_node->name)))
		new_node->type = 4;
	else if (!(new_node = init_node(new_node, directory)))
		return (NULL);
	tree = place_node(tree, new_node, mode);
	return (tree);
}
