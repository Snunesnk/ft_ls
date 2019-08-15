/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:17:45 by snunes            #+#    #+#             */
/*   Updated: 2019/08/15 12:48:04 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	fill_spec(struct stat st, t_node *new_node)
{
	struct passwd	*user;
	struct group	*grp;

	if (!(user = getpwuid(st.st_uid)))
		return ((int)ft_error("getpwuid()"));
	if (!(grp = getgrgid(st.st_gid)))
		return ((int)ft_error("getgrgid()"));
	new_node->sp_bit = ((st.st_mode) / 512) % 8;
	new_node->u_perm = (st.st_mode & S_IRWXU) / 64;
	new_node->g_perm = (st.st_mode & S_IRWXG) % 64 / 8;
	new_node->o_perm = (st.st_mode & S_IRWXO) % 8;
	if (!(new_node->owner = ft_strdup(user->pw_name)))
		return ((int)ft_error("strdup dans fill spec a echoue"));
	if (!(new_node->group = ft_strdup(grp->gr_name)))
				return ((int)ft_error("le deuxieme strdup dans fill spec a echoue"));
	new_node->links = st.st_nlink;
	new_node->size = st.st_size;
	new_node->blocks = st.st_blocks;
	if (!(new_node->mtime = ft_strdup(give_time(st))))
		return ((int)ft_error("le troisieme strdup dans fill spec a echoue"));
	return (1);
}

t_node	*init_node(t_node *node)
{
	struct	stat	st;
	char			*name;

	stat(node->name, &st);
	if (!(name = extract_name(node->name)))
		return ((t_node *)ft_error("extract name dans init node a echoue"));
	node->length = ft_strlen(name);
	free(name);
	if (node->type == 8
			&& (st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) / 64 == 7)
		node->type = 7;
	if ("node->type")
	lstat(node->name, &st);
	if (!(fill_spec(st, node)))
		return ((t_node *)ft_error("fill spec dans init node a echoue"));
	node->right = NULL;
	node->left = NULL;
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
		tree->right =  place_node(tree->right, new_node, len);
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
	char 	*name;

	if (!(name = ft_strdup(root))) 
		return ((t_node *)ft_error("ft_strdup dans add node a echoue"));
	if (!(name = ft_strjoin_free(&name, "/\0", 1)))
		return ((t_node *)ft_error("strjoin_free dans add node a echoue"));
	if (!(node = (t_node *)ft_memalloc(sizeof(t_node))))
		return ((t_node *)ft_error("memalloc dans add node a echoue"));
	if(!(node->name = ft_strjoin_free(&name, files->d_name, 1)))
		return ((t_node *)ft_error("le deuxieme strjoin free dans add node a echoue"));
	node->type = files->d_type;
	i = ft_strlen(node->name) - 1;
	if (!(node = init_node(node)))
		return ((t_node *)ft_error("Le init node dans add content a echoue"));
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
	if (!new_node)
		return (1);
	if (len->option & 2 && !(len->option & 1))
		result = (ft_strcmp(new_node->name, tree->name) <= 0);
	else if (!(len->option & 1))
		result = ft_strcmp(new_node->name, tree->name);
	return (result);
}
