/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:53:15 by snunes            #+#    #+#             */
/*   Updated: 2019/08/12 18:26:43 by snunes           ###   ########.fr       */
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

	tree = NULL;
	if (!singleton(0))
		return (0);
	option = (int **)singleton(2);
	arg = get_options(argv, option);
	if (argc - arg > 1 || **option & 16)
		**option = **option | 32;
	if (argc - arg == 0)
		tree = add_content(tree, ".\0");
	while (argc > arg)
	{
		tree = add_content(tree, argv[arg]);
		arg++;
	}
	ft_printf("content added, preparation for print\n");
	ft_printf("premiere node: %s, heigth = %d\n", tree->name, tree->heigth);
	print_tree(tree, argv);
	if (!(**option & 4))
		ft_printf("\n");
	return (0);
}
