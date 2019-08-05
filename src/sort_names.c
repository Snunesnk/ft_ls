/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_names.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:33:50 by snunes            #+#    #+#             */
/*   Updated: 2019/08/05 12:49:20 by snunes           ###   ########.fr       */
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
	if (!(new_node->mtime = give_time(st)))
		return (0);
	update_l(len, new_node, options);
	return (1);
}

int	add_elem(t_node *new_node, struct dirent *files, t_length *len, t_opt *opt)
{
	struct stat st;

	stat(files->d_name, &st);
	if (!(new_node->name = ft_strdup(files->d_name)))
		return (0);
	new_node->length = ft_strlen(files->d_name);
	if (files->d_type == 8
			&& (st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) / 64 == 7)
		new_node->type = 7;
	else
		new_node->type = files->d_type;
	lstat(files->d_name, &st);
	fill_spec(st, new_node, len, opt);
	new_node->right = NULL;
	new_node->left = NULL;
	return (1);
}

int	sort_tree(t_opt *options, t_node *new_node, t_node *tmp_tree)
{
	if (options->opt_r && !options->opt_t)
	{
		if (ft_strcmp(new_node->name, tmp_tree->name) <= 0)
			return (1);
		return (0);
	}
	else if (!options->opt_t)
		return (ft_strcmp(new_node->name, tmp_tree->name));
	else if (options->opt_r)
		return (0);
	else
		return (0);
}

int	add_node(struct dirent *files, t_node **names, t_opt *option, t_length *len)
{
	t_node	*new_node;
	t_node	*tmp_node;
	t_node	*tmp_tree;

	tmp_tree = *names;
	if (!(new_node = (t_node *)ft_memalloc(sizeof(t_node))))
			return (0);
	if (!(add_elem(new_node, files, len, option)))
	{
		free(new_node);
		return (0);
	}
	while (tmp_tree)
	{
		tmp_node = tmp_tree;
		if (sort_tree(option, new_node, tmp_tree) <= 0)
		{
			tmp_tree = tmp_tree->left;
			if (!tmp_tree)
				tmp_node->left = new_node;
		}
		else
		{
			tmp_tree = tmp_tree->right;
			if (!tmp_tree)
				tmp_node->right = new_node;
		}
	}
	return (1);
}

int		organize_names(t_node *names, DIR *dir, t_opt *options, t_length *len)
{
	struct dirent	*files;

	files = readdir(dir);
	len->name_l = 0;
	len->link_l = 0;
	len->user_l = 0;
	len->group_l = 0;
	len->size_l = 0;
	if (!(add_elem(names, files, len, options)))
		return (0);
	while ((files = readdir(dir)))
		add_node(files, &names, options, len);
	return (1);
}
