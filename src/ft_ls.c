/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:53:15 by snunes            #+#    #+#             */
/*   Updated: 2019/08/12 13:54:41 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_length	*init_len(t_length **len)
{
	*len = (t_length *)ft_memalloc(sizeof(t_length));
	(*len)->name_l = 0;
	(*len)->size_l = 0;
	(*len)->link_l = 0;
	(*len)->group_l = 0;
	(*len)->user_l = 0;
	(*len)->blocks = 0;
	return (*len);
}

char	**sing_path(char *to_add)
{
	int			i;
	static char *path;

	if (!to_add)
	{
		if (!path && !(path = ft_memalloc(sizeof(char))))
			return (0);
		else
			return (&path);
	}
	else if (!*to_add)
	{
//		ft_printf("path before up = %s\n", path);
		i = ft_strlen(path) - 1;
		while (path[i] != '/' && i >= 0)
			path[i--] = '\0';
		while (path[i] == '/' && i > 0)
			path[i--] = '\0';
//		ft_printf("path after  up = %s\n", path);
	}
	else if (!ft_strequ(path, to_add))
	{
//		ft_printf("join de %s et %s\n", path, to_add);
		if (*path)
			path = ft_strjoin_free(&path, "/\0", 1);
		path = ft_strjoin_free(&path, to_add, 1);
//		ft_printf("path n-epur = %s\n", path);
		while (ft_occur(".//\0", path))
			ft_memmove(path, path + 3, sizeof(path));
		while (ft_occur("./\0", path))
			ft_memmove(path, path + 2, sizeof(path));
//		ft_printf("path y-epur = %s\n", path);
	}
	return (&path);
}

void	**singleton(int nb)
{
	static int		*option;
	static t_length	*len;

	if (nb == 0)
	{
		if (!(len = init_len(&len)))
			return (0);
		if (!(option = (int *)ft_memalloc(sizeof(int))))
			return (0);
	}
	if (nb == 2)
		return ((void *)&option);
	if (nb == 3)
		return ((void **)(&len));
	return ((void **)3);
}

int		get_options(char **argv, int **option)
{
	int i;
	
	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		**option = (ft_occur("t\0", argv[i])) ? **option | 1 : **option;
		**option = (ft_occur("r\0", argv[i])) ? **option | 2 : **option;
		**option = (ft_occur("l\0", argv[i])) ? **option | 4 : **option;
		**option = (ft_occur("a\0", argv[i])) ? **option | 8 : **option;
		**option = (ft_occur("R\0", argv[i])) ? **option | 16 : **option;
		i++;
	}
	**option = **option | 64;
	return (i);
}

int		main(int argc, char **argv)
{
	int		arg;
	t_node	*tree;
	int		**option;
	char	*root;

	tree = NULL;
	if (!singleton(0) || !sing_path(NULL))
		return (0);
	option = (int **)singleton(2);
	arg = get_options(argv, option);
	if (argc - arg > 1 || **option & 16)
		**option = **option | 32;
	if (argc - arg == 0)
		tree = start_tree(tree, "./\0", ".\0");
	while (argc > arg)
	{
		root = find_root(root, argv[arg]);
//		sing_path(root);
		tree = start_tree(tree, root, argv[arg]);
		arg++;
	}
	print_tree(tree, 1);
	if (!(**option & 4))
		ft_printf("\n");
	return (0);
}
