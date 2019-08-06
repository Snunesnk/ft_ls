/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 12:14:46 by snunes            #+#    #+#             */
/*   Updated: 2019/08/06 15:33:10 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_options(int argc, char **argv, t_opt *option)
{
	int i;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		option->opt = ft_occur("R\0", argv[i]) ? option->opt | 16 : option->opt;
		option->opt = ft_occur("a\0", argv[i]) ? option->opt | 8 : option->opt;
		option->opt = ft_occur("l\0", argv[i]) ? option->opt | 4 : option->opt;
		option->opt = ft_occur("r\0", argv[i]) ? option->opt | 2 : option->opt;
		option->opt = ft_occur("t\0", argv[i]) ? option->opt | 1 : option->opt;
		i++;
	}
	return (i);
}

t_node	*read_all(t_node *tree, char *to_add, t_opt *options)
{
	DIR				*directory;
	t_length		len;


	len.name_l = 0;
	len.link_l = 0;
	len.user_l = 0;
	len.group_l = 0;
	len.size_l = 0;
	len.blocks = 0;
	if ((directory = opendir(to_add)))
	{
		tree = create_tree(directory, tree, options);
		closedir(directory);
	}
	else
		new_node.type = 0;
	tree = add_node(tree, options);
	return (tree);
}
/*
		if (i + 1 < argc)
			option->multi_dir = 1;
		if (option->multi_dir == 1)
			ft_printf("%s:\n", argv[i]);
		if (option->opt & 16)
			ft_printf("\n%.*s:\n", ft_strlen(option->path) - 1, option->path);
		print_asked(directory, option);
		if (option->multi_dir == 1 && i + 1 < argc)
			ft_printf("\n");
		}
		else
			ft_printf("%s  ", argv[i]);
		i++;
	}
}
*/
int		main(int argc, char **argv)
{
	t_opt			options;
	int				arg;
	int				i;
	t_node			tree;

	i = 1;
	&tree = NULL;
	if (!(options.path = ft_strdup(".\0")))
		return (0);
	options.opt = 0;
	arg = get_options(argc, argv, &options);
	while (argv[i] || i == 1)
	{
		if (i == 1 && !argv[i])
			read_all(&tree, ".", options);
		else
			read_all(&tree, argv[i], options);
		i++;
	}
	fill_tree_spec(&tree, ".");
	return (0);
}
