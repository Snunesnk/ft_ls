/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:17:45 by snunes            #+#    #+#             */
/*   Updated: 2019/08/13 20:23:16 by snunes           ###   ########.fr       */
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

t_node	*init_node(t_node *node)
{
	struct	stat	st;
	char			*name;

	stat(node->name, &st);
	name = extract_name(node->name);
	node->length = ft_strlen(name);
	free(name);
	if (node->type == 8
			&& (st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) / 64 == 7)
		node->type = 7;
	lstat(node->name, &st);
	fill_spec(st, node);
	node->right = NULL;
	node->left = NULL;
	node->heigth = 1;
	return (node);
}

t_node	*place_node(t_node *tree, t_node *new_node)
{
	int balanced;

	if (!tree)
		return (new_node);
	if (ft_node_cmp(tree, new_node) <= 0)
		tree->left = place_node(tree->left, new_node);
	else
		tree->right =  place_node(tree->right, new_node);
	tree->heigth = 1 + MAX(heigth(tree->left), heigth(tree->right));
	balanced = check_balance(tree);
	if (balanced < -1 || balanced > 1)
		tree = balance(balanced, tree, new_node);
	return (tree);
}

t_node	*add_node(t_node *tree, struct dirent *files, char *root)
{
	t_node	*node;
	int		i;
	char 	*name;

	if (!(name = ft_strdup(root))) 
		return (NULL);
	if (!(name = ft_strjoin_free(&name, "/\0", 1)))
		return (NULL);
	if (!(node = (t_node *)ft_memalloc(sizeof(t_node))))
		return (NULL);
	if(!(node->name = ft_strjoin_free(&name, files->d_name, 1)))
		return (NULL);
	node->type = files->d_type;
	i = ft_strlen(node->name) - 1;
	if (!(node = init_node(node)))
		return (NULL);
	tree = place_node(tree, node);
	return (tree);
}

int		ft_node_cmp(t_node *tree, t_node *new_node)
{
	int			result;
	t_length	*len;
	char		*root;

	root = find_root(tree->name);
	len = *singleton(root);
	free(root);
	if (!tree)
		return (-1);
	if (!new_node)
		return (1);
	result = path_cmp(new_node->name, tree->name);
	if (result < 0 || result > 0)
		return (result);
	else if (len->option & 2 && !(len->option & 1))
		result = (ft_strcmp(new_node->name, tree->name) <= 0);
	else if (!(len->option & 1))
		result = ft_strcmp(new_node->name, tree->name);
	return (result);
}
