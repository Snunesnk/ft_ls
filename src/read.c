/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 12:42:46 by snunes            #+#    #+#             */
/*   Updated: 2019/08/03 17:46:45 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	print_perms(int perm)
{
	if (perm == 7)
		ft_printf("rwx");
	if (perm == 6)
		ft_printf("rw-");
	if (perm == 5)
		ft_printf("r-x");
	if (perm == 4)
		ft_printf("r--");
	if (perm == 3)
		ft_printf("-wx");
	if (perm == 2)
		ft_printf("-w-");
	if (perm == 1)
		ft_printf("--x");
	if (perm == 0)
		ft_printf("---");
}

void	print_info(t_node *names, t_length *len)
{
	char	file_type[20];
	int		i;

	i = 0;
	init_file_type(file_type);
	while (names->type != file_type[i] && file_type[i])
		i += 2;
	ft_printf("%c", file_type[i + 1]);
	print_perms(names->u_perm);
	print_perms(names->g_perm);
	print_perms(names->o_perm);
	i = 0;
	while (ft_nbrlen(names->links) + i < len->link_l + 2)
	{
		i++;
		write(1, " ", 1);
	}
	ft_printf("%d ", names->links);
//	print_next(names, len);
}

int	print_tree(t_node *names, t_opt *options, t_length *len)
{
	if (!names)
		return (0);
	if (names->left)
		print_tree(names->left, options, len);
	if ((names->name[0] != '.' || options->opt_a == 1))
	{
		if (options->opt_l)
			print_info(names, len);
		if (names->type == 4)
			ft_printf("{B_cyan}%s", names->name);
		else if (names->type == 7)
			ft_printf("{red}%s", names->name);
		else if (names->type == 10)
			ft_printf("{purple}%s", names->name);
		else
			ft_printf("%s", names->name);
		while (len->name_l > names->length++ && !options->opt_l)
			write(1, " ", 1);
		if (options->opt_l)
			write(1, "\n", 1);
	}
	if (names->right)
		print_tree(names->right, options, len);
	return (1);
}

void		print_asked(DIR *directory, t_opt *options)
{
	t_node		names;
	t_length	len;

	organize_names(&names, directory, options, &len);
	print_tree(&names, options, &len);
	if (!options->opt_l)
		ft_printf("\n");
}

void		read_all(int i, char **argv, int argc, t_opt *options)
{
	DIR	*directory;

	if (i >= argc || !argv[i] || options->opt_R)
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
