/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 12:14:46 by snunes            #+#    #+#             */
/*   Updated: 2019/08/06 16:25:09 by snunes           ###   ########.fr       */
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

t_node	*read_all(t_node *tree, char *to_add, t_opt *options, t_length *len)
{
	DIR				*root;
	struct dirent	*files;
	t_node			new_node;

	root = opendir(options->path);
	files = readdir(root);
	while (!ft_strequ(files->d_name, to_add))
		files = readdir(root);
	fill_node(&new_node, files, len, options);
	ft_printf("name = %s\n", new_node.name);
	tree = place_node(tree, &new_node, options);
	return (tree);
}

void	init_len(t_length *len)
{
	len->name_l = 0;
	len->size_l = 0;
	len->link_l = 0;
	len->user_l = 0;
	len->group_l = 0;
	len->blocks = 0;
}

int		main(int argc, char **argv)
{
	t_opt			options;
	int				arg;
	int				i;
	t_node			tree;
	t_length		len;

	i = 1;
	init_len(&len);
	if (!(options.path = ft_strdup("./\0")))
		return (0);
	options.opt = 0;
	arg = get_options(argc, argv, &options);
	while (i < argc || i == 1)
	{
		if (i == 1 && !argv[i])
			read_all(&tree, ".", &options, &len);
		else
			read_all(&tree, argv[i], &options, &len);
		i++;
	}
	print_tree(&tree, &options, &len);
	return (0);
}
