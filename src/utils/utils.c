/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 11:13:08 by snunes            #+#    #+#             */
/*   Updated: 2019/09/08 16:09:47 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*extract_name(char *path)
{
	char	*name;
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (path[++i])
	{
		if (path[i] == '/' && path[i + 1])
			j = i + 1;
	}
	if (!j)
		return (ft_strdup("."));
	i = (path[i] == '/') ? i - 1 : i;
	if (!(name = (char *)ft_memalloc(sizeof(char) * (i - j + 1))))
		return (NULL);
	i = 0;
	while (path[j])
	{
		name[i] = path[j];
		i++;
		j++;
	}
	name[i] = '\0';
	return (name);
}

char	*find_root(char *file)
{
	int		i;
	int		j;
	char	*root;

	if (!(root = ft_strdup(file)))
		return (NULL);
	i = 0;
	j = -1;
	while (root[i] && i + 1 < (int)ft_strlen(root))
	{
		if (root[i] == '/')
			j = i + 1;
		i++;
	}
	if (j > 0)
		root[j] = '\0';
	else if (j < 0)
	{
		root[0] = '.';
		root[1] = 0;
	}
	return (root);
}

int		requi(t_length *len, char *name, int mode)
{
	if ((ft_strequ(name, ".\0") || ft_strequ(name, "..\0")) && !mode)
	{
		if (len->option & 64)
			return (1);
		return (0);
	}
	if (name[0] != '.')
		return (1);
	if (name[0] == '.' && (ft_strequ(name, "./") || len->option & 8
				|| len->option & 64))
		return (1);
	return (0);
}

void	print_dir(t_node *tree, t_length *len, int mode)
{
	if (mode && mode != 3)
	{
		if (!(len->option & 4) && len->option & 128)
			ft_printf("\n");
		if (len->option & 128 && tree->type)
			ft_printf("\n");
		if ((len->option & 32) || (len->option & 16 && len->option & 128))
			ft_printf("%s:\n", tree->path);
	}
	if (!mode || (mode == 3 && (len->option & 256)))
		ft_printf("total %d\n", len->blocks);
	len->option += (len->option & 128 && tree->type != 20) ? 0 : 128;
}

t_node	*node_type(t_node *node, t_length *len)
{
	int	res;
	DIR	*dir;

	dir = opendir(node->path);
	if (!dir)
		return (node);
	res = node->type;
	if (node->type != 4 || ft_strequ(node->path, "/dev/fd"))
	{
		if (node->type == 10 && (len->option & 256)
				&& !(node->name[ft_strlen(node->name) - 1] == '/'))
			node->type = 10;
		else
			node->type = 4;
	}
	if (node->type != res && !ft_strequ(node->path, "/dev/fd"))
		node->changed = 1;
	closedir(dir);
	return (node);
}
