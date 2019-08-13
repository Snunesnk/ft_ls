/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:53:15 by snunes            #+#    #+#             */
/*   Updated: 2019/08/13 20:23:15 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_length	*init_len(t_length *len, char *path)
{
	t_length	*new_len;

	new_len = (t_length *)ft_memalloc(sizeof(t_length));	
	if (!path)
	{
		new_len->path = NULL;
		new_len->prev = NULL;
		new_len->option = 0;
	}
	else
	{
		new_len->option = len->option;
		if (!(new_len->path = ft_strdup(path)))
			return (NULL);
		new_len->prev = len;
	}
	new_len->name_l = 0;
	new_len->size_l = 0;
	new_len->link_l = 0;
	new_len->group_l = 0;
	new_len->user_l = 0;
	new_len->blocks = 0;
	new_len->next = NULL;
	return (new_len);
}

t_length	**singleton(char *path)
{
	static t_length	*len;

	if (!path)
	{
		if (!(len = init_len(len, NULL)))
			return (NULL);
		return (&len);
	}
	while (len->prev)
		len = len->prev;
	if (*path)
	{
		while (!ft_strequ(len->path, path) && len->next)
			len = len->next;
		if (!len->next)
		{
			if (!(len->next = init_len(len, path)))
				return (NULL);
			len = len->next;
		}
	}
	while (!*path && len->next)
	{
		len->option = (len->option & 64) ? len->option - 64 : len->option;
		len = len->next;
	}
	return (&len);
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
	t_length	**len;
	char		*name;

	tree = NULL;
	if (!singleton(0))
		return (0);
	len = singleton(NULL);
	arg = get_options(argv, &((*len)->option));
	if (argc - arg > 1 || (*len)->option & 16)
		(*len)->option = (*len)->option | 32;
	if (argc - arg == 0)
		tree = add_content(tree, ".\0");
	while (argc > arg)
	{
		tree = add_content(tree, argv[arg]);
		arg++;
	}
	name = ft_strdup(*argv);
	print_tree(tree, &name);
	free(name);
	if (!((*len)->option & 4))
		ft_printf("\n");
	free_len(*len);
	return (0);
}
