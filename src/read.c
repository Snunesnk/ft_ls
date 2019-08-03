/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 12:42:46 by snunes            #+#    #+#             */
/*   Updated: 2019/08/03 11:52:49 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int	print_tree(t_node *names, t_opt *options, int name_l)
{
	if (!names)
		return (0);
	if (names->left)
		print_tree(names->left, options, name_l);
	if ((names->name[0] != '.' || options->opt_a == 1))
	{
		if (names->type == 4)
			ft_printf("{B_cyan}%s", names->name);
		else
			ft_printf("%s", names->name);
		while (name_l > names->length++ && !options->opt_l)
			write(1, " ", 1);
		if (options->opt_l)
			write(1, "\n", 1);
	}
	if (names->right)
		print_tree(names->right, options, name_l);
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
	t_node	names;
	int		name_l;

	name_l = organize_names(&names, directory, options) + 1;
	print_tree(&names, options, name_l);
	if (!options->opt_l)
		ft_printf("\n");
}

void		read_all(int i, char **argv, int argc, t_opt *options)
{
	DIR	*directory;

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
