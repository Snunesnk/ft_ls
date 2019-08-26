/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:53:15 by snunes            #+#    #+#             */
/*   Updated: 2019/08/26 16:36:42 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_length	*init_len(t_length *len)
{
	t_length	*new_len;

	if (!(new_len = (t_length *)ft_memalloc(sizeof(t_length))))
		return (NULL);
	if (!len)
		new_len->option = 0;
	else
	{
		new_len->option = len->option;
		if (len->option & 64)
			new_len->option -= 64;
	}
	new_len->column = 0;
	new_len->name_l = 0;
	new_len->size_l = 0;
	new_len->link_l = 0;
	new_len->group_l = 0;
	new_len->user_l = 0;
	new_len->blocks = 0;
	return (new_len);
}

int			get_options(char **argv, int *option)
{
	int		i;
	int		j;
	char	ret;

	i = 1;
	while (argv[i] && argv[i][0] == '-' && argv[i][1])
	{
		j = 1;
		while (argv[i][j])
		{
			ret = argv[i][j + 1];
			argv[i][j + 1] = '\0';
			if (ft_occur(argv[i] + j, "tr 1   a       R"))
				*option |= ft_occur(argv[i] + j, "tr 1   a       R");
			else if ((argv[i][j] == 'l' && !(*option & 256)) || argv[i][j] == 'G')
				*option += (argv[i][j] = 'G') ? 512 : 256;
			else if ((argv[i][j] != '-' || j > 2))
				return (-ft_printf("ls: illegal option -- %c\n", argv[i][j]));
			argv[i][j + 1] = ret;
			j++;
		}
		i++;
	}
	*option |= (*option & 256 && !(*option & 4)) ? 68 : 64;
	return (i);
}

int			main(int argc, char **argv)
{
	int			arg;
	t_node		*tree;
	t_length	*len;

	tree = NULL;
	if (!(len = init_len(NULL)))
		return (1);
	if ((arg = get_options(argv, &(len->option))) < 0)
		return (ft_printf("usage: ls [-Ralrt] [file ...]\n"));
	if (argc - arg == 0 && !(tree = add_content(tree, ".\0", len)))
		return (1);
	len->option += (argc - arg > 1) ? 32 : 0;
	while (argc > arg)
	{
		tree = add_content(tree, argv[arg], len);
		arg++;
	}
	if (!tree)
		return (1);
	print_first(tree, len);
	if (len->option & 16)
		print_recurs(tree, len);
	(len->option & 4) ? 0 : ft_printf("\n");
	free(len);
	free_tree(tree);
	return (0);
}
