/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:17:45 by snunes            #+#    #+#             */
/*   Updated: 2019/08/26 12:35:56 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		fill_spec(struct stat st, t_node *new_node)
{
	struct passwd	*user;
	struct group	*grp;

	user = getpwuid(st.st_uid);
	grp = getgrgid(st.st_gid);
	new_node->sp_bit = ((st.st_mode) / 512) % 8;
	new_node->u_perm = (st.st_mode & S_IRWXU) / 64;
	new_node->g_perm = (st.st_mode & S_IRWXG) % 64 / 8;
	new_node->o_perm = (st.st_mode & S_IRWXO) % 8;
	new_node->owner = (user) ? ft_strdup(user->pw_name) : ft_strdup("4389\0");
	new_node->group = (grp) ? ft_strdup(grp->gr_name) : ft_strdup("daemon\0");
	if (!new_node->group || !new_node->group)
		return (0);
	new_node->links = st.st_nlink;
	new_node->size = st.st_size;
	new_node->blocks = st.st_blocks;
	if (!(new_node->mtime = ft_strdup(ctime(&st.st_mtimespec.tv_sec))))
		return (0);
	new_node->mtime = adjust_time(new_node->mtime);
	return (1);
}

t_node	*init_node(t_node *node)
{
	struct stat	st;
	char		*name;

	node->right = NULL;
	node->left = NULL;
	stat(node->name, &st);
	if (!(name = extract_name(node->name)))
		return (NULL);
	node->length = ft_strlen(name);
	free(name);
	if (node->type == 8
			&& (st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) / 64 == 7)
		node->type = 7;
	lstat(node->name, &st);
	if (!(fill_spec(st, node)))
		return (NULL);
	node->heigth = 1;
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
	int		i;

	if (!(node = (t_node *)ft_memalloc(sizeof(t_node))))
		return (NULL);
	if (len->option & 64)
		node->name = ft_strdup(root);
	else
		node->name = creat_path(root, files->d_name);
	if (!node->name)
		return (NULL);
	node->type = files->d_type;
	i = ft_strlen(node->name) - 1;
	if (!(node = init_node(node)))
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
		result = ft_strcmp(new_node->name, tree->name);
	if (len->option & 2)
		result = -result;
	return (result);
}
