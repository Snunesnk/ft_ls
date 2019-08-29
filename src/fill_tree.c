/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:17:45 by snunes            #+#    #+#             */
/*   Updated: 2019/08/29 16:26:55 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		fill_spec(struct stat st, t_node *new_node, t_length *len)
{
	struct passwd	*user;
	struct group	*grp;

	if (!(new_node->mtime = ft_strdup(ctime(&st.st_mtimespec.tv_sec))))
		return (0);
	new_node->mtime = adjust_time(new_node->mtime);
	if (!(len->option & 256))
		return 1;
	user = getpwuid(st.st_uid);
	grp = getgrgid(st.st_gid);
	new_node->owner = (user) ? ft_strdup(user->pw_name) : ft_strdup("4389\0");
	new_node->group = (grp) ? ft_strdup(grp->gr_name) : ft_strdup("wheel\0");
	if (!new_node->group || !new_node->group)
		return (0);
	new_node->size = st.st_size;
	new_node->blocks = st.st_blocks;
	return (1);
}

t_node	*init_node(t_node *node, t_length *len)
{
	struct stat	st;

	node->right = NULL;
	node->left = NULL;
	node->mtime = NULL;
	node->owner = NULL;
	node->group = NULL;
	node->heigth = 1;
	node->length = ft_namelen(node->name);
	lstat(node->path, &st);
	node->links = st.st_nlink;
	if ((len->option & 512) || (len->option & 256))
	{
		node->sp_bit = ((st.st_mode) / 512) % 8;
		node->u_perm = (st.st_mode & S_IRWXU) / 64;
		node->g_perm = (st.st_mode & S_IRWXG) % 64 / 8;
		node->o_perm = (st.st_mode & S_IRWXO) % 8;
		if (node->type == 8 && IS_EXEC(node->o_perm))
			node->type = 7;
	}
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
	if ((len->option & 64))
		node->length = ft_strlen(node->name);
	update_l(node, len);
	tree = place_node(tree, node, len);
	return (tree);
}

int		ft_node_cmp(t_node *tree, t_node *new_node, t_length *len)
{
	int			result;

	result = 0;
	if (!tree)
		return (-1);
	if (len->option & 64)
	{
		if ((tree->type == 4 && new_node->type != 4)
				|| (tree->type != 4 && new_node->type == 4))
			return (new_node->type == 4);
	}
	if (!new_node)
		return (1);
	if ((len->option & 1))
		result = (ft_tmpcmp(new_node->mtime, tree->mtime));
	if (result == 0)
		result = ft_strcmp(new_node->path, tree->path);
	if (len->option & 2)
		result = -result;
	return (result);
}
