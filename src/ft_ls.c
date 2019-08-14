/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:53:15 by snunes            #+#    #+#             */
/*   Updated: 2019/08/14 17:46:02 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_length	*init_len(t_length *len)
{
	t_length	*new_len;

	new_len = (t_length *)ft_memalloc(sizeof(t_length));	
	if (!len)
	{
		new_len->option = 0;
		new_len->multi = 0;
	}
	else
	{
		new_len->option = len->option;
		new_len->multi = len->multi;
	}
	new_len->name_l = 0;
	new_len->size_l = 0;
	new_len->link_l = 0;
	new_len->group_l = 0;
	new_len->user_l = 0;
	new_len->blocks = 0;
	return (new_len);
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
	}
	*option = *option | 64;
	return (i);
}

int		main(int argc, char **argv)
{
	int			arg;
	t_node		*tree;
	t_length	*len;
	char		*name;

	len = NULL;
	tree = NULL;
	if (!(len = init_len(len)))
		return (0);
	arg = get_options(argv, &(len->option));
	if (argc - arg > 1 || len->option & 16)
		len->option = len->option | 32;
	if (argc - arg == 0)
		tree = add_content(tree, ".\0", len);
	while (argc > arg)
	{
		tree = add_content(tree, argv[arg], len);
		arg++;
	}
	name = ft_strdup(*argv);
	print_tree(tree, &name, len);
	if (len->option & 16)
		print_recurs(tree, len);
	free(name);
	free(len);
	return (0);
}
