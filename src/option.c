/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:10:13 by snunes            #+#    #+#             */
/*   Updated: 2019/08/13 20:23:18 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	update_l(t_node *node)
{
	t_length	**len;
	char		*name;
	char		*root;

	name = extract_name(node->name);
	root = find_root(node->name);
	len = singleton(root);
	free(root);
	if (ft_strlen(name) + 1 > (size_t)(*len)->name_l
			&& (name[0] != '.' || (*len)->option & 8))
		(*len)->name_l = ft_strlen(name) + 1;
	if (ft_nbrlen(node->links) + 2 > (*len)->link_l
					&& (name[0] != '.' || (*len)->option & 8))
		(*len)->link_l = ft_nbrlen(node->links) + 2;
	if (ft_strlen(node->owner) + 1 > (size_t)(*len)->user_l
					&& (name[0] != '.' || (*len)->option & 8))
		(*len)->user_l = ft_strlen(node->owner);
	if (ft_strlen(node->group) + 2 > (size_t)(*len)->group_l
					&& (name[0] != '.' || (*len)->option & 8))
		(*len)->group_l = ft_strlen(node->group);
	if (ft_nbrlen(node->size) + 2 > (*len)->size_l
					&& (name[0] != '.' || (*len)->option & 8))
		(*len)->size_l = ft_nbrlen(node->size) + 2;
	if ((name[0] != '.' || (*len)->option & 8))
		(*len)->blocks += node->blocks;
	free(name);
}

void	init_file_type(char file_type[20])
{
	file_type[0] = 1;
	file_type[2] = 2;
	file_type[4] = 4;
	file_type[6] = 6;
	file_type[8] = 7;
	file_type[10] = 8;
	file_type[12] = 10;
	file_type[14] = 12;	
	file_type[16] = 14;
	file_type[18] = 0;
	file_type[1] = 'p';
	file_type[3] = 'c';
	file_type[5] = 'd';
	file_type[7] = 'b';
	file_type[9] = '-';
	file_type[11] = '-';
	file_type[13] = 'l';
	file_type[15] = 's';
	file_type[17] = 0;
	file_type[19] = 0;
}

int		give_length(int length, int to_reach)
{
	while (length < to_reach)
		length++;
	return (length);
}

char	*give_time(struct stat st)
{
	char	*ltime;

	ltime = ctime(&st.st_mtimespec.tv_sec);
	ft_memmove(ltime, ltime + 4, 26);
	ltime[12] = '\0';
	return (ltime);
}

int		requi(t_length *len, char *name)
{
	if (ft_strequ(name, ".\0") || ft_strequ(name, "..\0"))
		return (0);
	if (name[0] != '.')
		return (1);
	if (name[0] == '.' && len->option & 8)
		return (1);
	return (0);
}

t_node	*add_recurs(t_node *tree, char *name)
{
	DIR				*dir;
	struct dirent	*file;
	t_length		*len;
	char			*root;

	ft_printf("ouverture de %s\n", name);
	root = ft_strdup(name);
	if (ft_strequ(root, ".\0"))
	{
		free(root);
		root = ft_strdup(name);
	}
	len = *singleton(name);
	dir = opendir(name);
	while ((file = readdir(dir)))
	{
		if (len->option & 16 && file->d_type == 4 && requi(len, file->d_name))
		{
			root = ft_strjoin_free(&root, "/\0", 1);
			root = ft_strjoin_free(&root, file->d_name, 1);
			tree = add_recurs(tree, root);
			if (tree->heigth >= 11)
			{
				print_tree(tree, &root);
				tree = add_content(tree, root);
		ft_printf("print du tree effectue, root = %s\n", root);
			}
			free(root);
			root = ft_strdup(name);
		}
		tree = add_node(tree, file, root);
		//ft_printf("tree->heigth = %d\n", tree->heigth);
	}
	closedir(dir);
	free(root);
	return (tree);
}
