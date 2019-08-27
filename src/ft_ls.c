/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:53:15 by snunes            #+#    #+#             */
/*   Updated: 2019/08/27 19:26:17 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_length	*init_len(t_length *len)
{
	t_length	*new_len;

	if (!(new_len = (t_length *)ft_memalloc(sizeof(t_length))))
		return (NULL);
	if (!len)
		new_len->option = 64;
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

void		init_poss(char **poss)
{
	poss[0] = "t1\0";
	poss[1] = "r2\0";
	poss[2] = "14\0";
	poss[3] = "a8\0";
	poss[4] = "R16\0";
	poss[5] = "l256\0";
	poss[6] = "G512\0";
	poss[7] = "\0";
}

int			get_options(char **argv, int *option)
{
	char	*poss[8];
	int		i;
	int		j;
	int		k;

	init_poss(poss);
	i = 1;
	while (argv[i] && argv[i][0] == '-' && argv[i][1])
	{
		j = 1;
		while (argv[i][j])
		{
			k = 0;
			while (poss[k][0] != argv[i][j] && poss[k][0])
				k++;
			if (!poss[k][0] && !(argv[i][j] == '-' && j <= 2 && !argv[i][j + 1]))
				return (-ft_printf("ft_ls: illegal option -- %c\n", argv[i][j]));
			*option |= ft_atoi(poss[k] + 1);
			if (argv[i][j] == '1' && (*option & 256))
				*option -= 256;
			j++;
		}
		i++;
	}
	*option += ((*option & 256) && !(*option & 4)) ? 4 : 0;
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
		return (ft_printf("usage: ./ft_ls [-GRalrt1] [file ...]\n"));
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
	free(len);
	free_tree(tree);
	return (0);
}
