/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:53:15 by snunes            #+#    #+#             */
/*   Updated: 2019/08/06 18:39:16 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_length	*init_len(t_lengh *len)
{
	if (!(len
}

void	*singleton(int nb)
{
	static char		*path;
	static int		option;
	static t_length	*len;

	if (nb == 0)
	{
		if (!(path = ft_strdup("./\0")))
				return (0);
		if (!(len = init_len(len)))
			return (0);
	}
	if (nb == 1)
		return ((void *)path);
	if (nb == 2)
		return (&option);
	if (nb == 3)
		return ((void *)len);
	return (path);
}

int		get_options(char **argv, int *option)
{
	int i;
	
	i = 1;
	while ( argv[i] && argv[i][0] == '-')
	{
		*option = (ft_occur(argv[i], "t\0")) ? *option & 1 : *option;
		*option = (ft_occur(argv[i], "r\0")) ? *option & 2 : *option;
		*option = (ft_occur(argv[i], "l\0")) ? *option & 4 : *option;
		*option = (ft_occur(argv[i], "a\0")) ? *option & 8 : *option;
		*option = (ft_occur(argv[i], "R\0")) ? *option & 16 : *option;
		i++;
	}
	return (i);
}

int		main(int argc, char **argv)
{
	int		arg;
	t_node	*tree;

	tree = NULL;
	(void)argc;
	singleton(0);
	arg = get_options(argv, (int *)singleton(2));
	while (argv[arg])
	{
		tree = creat_new_node(tree, argv[arg]);
		arg++;
	}
	if (arg == 1)
		tree = creat_new_node(tree, ".\0");
	return (0);
}
