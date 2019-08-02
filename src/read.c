/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 12:42:46 by snunes            #+#    #+#             */
/*   Updated: 2019/08/02 16:50:55 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int	print_tree(t_node *names, t_opt *options)
{
	if (!names)
		return (0);
	if (names->left)
		print_tree(names->left, options);
	if (names->name[0] != '.' || options->opt_a == 1)
	{
		if (names->type == 4)
			ft_printf("{B_cyan}%s", names->name);
		else
			ft_printf("%s", names->name);
	}
	if (names->right)
		print_tree(names->right, options);
	return (1);
}

unsigned int	get_info(char *path)
{
	struct stat	*buff;

	if (!(buff = (struct stat *)ft_memalloc(sizeof(stat))))
		return (0);
	lstat(path, buff);
	return (buff->st_nlink);
}

void		print_asked(DIR *directory, t_opt *options)
{
	t_node			names;

	organize_names(&names, directory);
	print_tree(&names, options);
	ft_printf("\n");
}

void		read_all(int i, char **argv, int argc, t_opt *options)
{
	DIR				*directory;

	if (i >= argc || !argv[i])
	{
		directory = opendir(".");
		print_asked(directory, options);
	}
	while (i < argc && argv[i])
	{
		if (i + 1 < argc)
			options->multi_dir = 1;
		if (options->multi_dir == 1)
			ft_printf("%s:\n", argv[i]);
		directory = opendir(argv[i]);
		print_asked(directory, options);
		if (options->multi_dir == 1 && i + 1 < argc)
			ft_printf("\n");
		i++;
	}
	closedir(directory);
}
