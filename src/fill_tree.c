/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:55:40 by snunes            #+#    #+#             */
/*   Updated: 2019/08/06 16:21:39 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int	fill_spec(struct stat st, t_node *new_node, t_length *len, t_opt *options)
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
	update_l(len, new_node, options);
	return (1);
}

int	fill_node(t_node *new, struct dirent *files, t_length *len, t_opt *opt)
{
	struct	stat st;
	char	*path;

	path = ft_strjoin(opt->path, files->d_name);
	stat(path, &st);
	if (!(new->name = ft_strdup(files->d_name)))
		return (0);
	new->length = ft_strlen(files->d_name);
	if (files->d_type == 8
			&& (st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) / 64 == 7)
		new->type = 7;
	else
		new->type = files->d_type;
	lstat(path, &st);
	fill_spec(st, new, len, opt);
	new->right = NULL;
	new->left = NULL;
	free(path);
	return (1);
}

int	sort_tree(t_opt *options, t_node *new_node, t_node *tree)
{
	if (new_node->type > tree->type)
		return (1);
	else if (new_node->type < tree->type)
		return (0);
	if (options->opt & 2 && !(options->opt & 1))
	{
		if (ft_strcmp(new_node->name, tree->name) <= 0)
			return (1);
		return (0);
	}
	else if (!(options->opt & 1))
		return (ft_strcmp(new_node->name, tree->name));
	else if (options->opt & 2)
		return (0);
	else
		return (0);
}

t_node *place_node(t_node *tree, t_node *new_node, t_opt *options)
{
	if (!tree)
		return (new_node);
	if (sort_tree(options, new_node, tree) <= 0)
		tree->left = place_node(tree->left, new_node, options);
	else
		tree->right = place_node(tree->right, new_node, options);
	return (tree);
}
