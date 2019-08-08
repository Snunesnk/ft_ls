/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:53:15 by snunes            #+#    #+#             */
/*   Updated: 2019/08/08 18:36:47 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_length	*init_len(t_length *len)
{
	len = (t_length *)ft_memalloc(sizeof(t_length));
	len->name_l = 0;
	len->size_l = 0;
	len->link_l = 0;
	len->group_l = 0;
	len->user_l = 0;
	len->blocks = 0;
	return (len);
}

char	**sing_path(char *to_add)
{
	int			i;
	static char *path;

	if (!to_add)
	{
		if (!(path = ft_memalloc(sizeof(char))))
			return (0);
	}
	else if (!*to_add)
	{
		i = ft_strlen(path) - 1;
		while (path[i] == '/' && i >= 0)
			path[i--] = '\0';
		while (path[i] != '/' && i >= 0)
			path[i--] = '\0';
	}
	else if (!ft_strequ(path, to_add))
	{
		if (*path && path[ft_strlen(path) - 1] != '/')
			path = ft_strjoin_free(&path, "/\0", 1);
		path = ft_strjoin_free(&path, to_add, 1);
	}
	return (&path);
}

void	*singleton(int nb)
{
	static int		option;
	static t_length	*len;

	if (nb == 0)
	{
		if (!(len = init_len(len)))
			return (0);
	}
	if (nb == 2)
		return (&option);
	if (nb == 3)
		return ((void *)len);
	return ((void *)3);
}

int		get_options(char **argv, int *option)
{
	int i;
	
	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		*option = (ft_occur("t\0", argv[i])) ? *option | 1 : *option;
		*option = (ft_occur("r\0", argv[i])) ? *option | 2 : *option;
		*option = (ft_occur("l\0", argv[i])) ? *option | 4 : *option;
		*option = (ft_occur("a\0", argv[i])) ? *option | 8 : *option;
		*option = (ft_occur("R\0", argv[i])) ? *option | 16 : *option;
		i++;
		up_a_dir(option->path, 2);
	}
	return (i);
}

int		main(int argc, char **argv)
{
	int				arg;
	t_node			*tree;
	DIR				*directory;
	int				*option;

	tree = NULL;
	if (!singleton(0) || !sing_path(NULL))
		return (0);
	option = (int *)singleton(2);
	arg = get_options(argv, option);
	if (argc - arg > 1 || *option & 16)
		*option = *option | 32;
	if (argc - arg == 0)
	{
		directory = opendir(".");
		tree = add_node(tree, ".\0", directory, 1);
		closedir(directory);
	}
	while (argv[arg])
	{
		directory = opendir(".");
		tree = add_node(tree, argv[arg], directory, 1);
		arg++;
		closedir(directory);
	}
	print_tree(tree, 1);
	if (!(*option & 4))
		ft_printf("\n");
	return (0);
}
