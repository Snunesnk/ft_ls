/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:17:45 by snunes            #+#    #+#             */
/*   Updated: 2019/09/06 12:54:44 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		fill_spec(struct stat st, t_node *node, t_length *len)
{
	struct passwd	*user;
	struct group	*grp;

	if (!(node->mtime = ft_strdup(ctime(&st.st_mtimespec.tv_sec))))
		return (0);
	node->mtime = adjust_time(node->mtime);
	if (!(len->option & 256))
		return (1);
	user = getpwuid(st.st_uid);
	grp = getgrgid(st.st_gid);
	node->owner = (user) ? ft_strdup(user->pw_name) : ft_strdup("4389\0");
	node->group = (grp) ? ft_strdup(grp->gr_name) : ft_strdup("wheel\0");
	if (!node->group || !node->group)
		return (0);
	node->size = st.st_size;
	if (len->option & 256 && (node->type == 2 || node->type == 6
															|| !node->type))
	{
		node->size = minor(st.st_rdev);
		node->major = major(st.st_rdev);
	}
	node->blocks = st.st_blocks;
	return (1);
}

t_node	*init_node(t_node *node, t_length *len)
{
	struct stat	st;

	if (node->type == 10 || len->option & 256)
		lstat(node->path, &st);
	else
		stat(node->path, &st);
	node->links = st.st_nlink;
	node = node_type(node, len);
	node->right = NULL;
	node->left = NULL;
	node->mtime = NULL;
	node->owner = NULL;
	node->group = NULL;
	node->heigth = 1;
	node->major = -1;
	node->length = ft_namelen(node->name);
	if ((len->option & 512) || (len->option & 256))
		add_perm(node, st);
	if ((len->option & 256 || len->option & 1) && !(fill_spec(st, node, len)))
		return (NULL);
	return (node);
}

t_node	*place_node(t_node *tree, t_node *new_node, t_length *len)
{
	int balanced;

	if (!tree)
		return (new_node);
	if (ft_node_cmp(tree, new_node, len) <= 0)
		tree->left = place_node(tree->left, new_node, len);
	else
		tree->right = place_node(tree->right, new_node, len);
	tree->heigth = 1 + MAX(heigth(tree->left), heigth(tree->right));
	balanced = check_balance(tree);
	if (balanced < -1 || balanced > 1)
		tree = balance(balanced, tree, new_node, len);
	return (tree);
}

t_node	*add_node(t_node *tree, struct dirent *files, char *root, t_length *len)
{
	t_node	*node;

	if (!(node = (t_node *)ft_memalloc(sizeof(t_node))))
		return (NULL);
	if (len->option & 64)
		node->path = ft_strdup(root);
	else
		node->path = creat_path(root, files->d_name);
	if (!node->path || !(node->name = extract_name(node->path)))
		return (NULL);
	if (ft_strequ(node->name, ".") && !ft_strequ(root, ".") && len->option & 64)
	{
		free(node->name);
		if (!(node->name = ft_strdup(root)))
			return (NULL);
	}
	node->type = files->d_type;
	if (!(node = init_node(node, len)))
		return (NULL);
	(ft_strequ(node->name, "etc") && len->option & 256) ? node->type = 10 : 0;
	if ((len->option & 64))
		node->length = ft_strlen(node->name);
	update_l(node, len);
	tree = place_node(tree, node, len);
	return (tree);
}

int		ft_node_cmp(t_node *tree, t_node *node, t_length *len)
{
	int	result;

	result = 0;
	if (!tree)
		return (-1);
	if (tree->type == 20 || node->type == 20)
	{
		if (tree->type == node->type)
			return (ft_strcmp(node->name, tree->name));
		return (tree->type - node->type);
	}
	if (len->option & 64)
	{
		if ((tree->type == 4 && node->type != 4)
				|| (tree->type != 4 && node->type == 4))
			return (node->type == 4);
	}
	if (!node)
		return (1);
	if ((len->option & 1))
		result = (ft_tmpcmp(node->mtime, tree->mtime));
	if (result == 0)
		result = ft_strcmp(node->path, tree->path);
	return ((len->option & 2) ? -result : result);
}
