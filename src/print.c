/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 12:42:46 by snunes            #+#    #+#             */
/*   Updated: 2019/08/05 20:50:12 by snunes           ###   ########.fr       */
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
	int		link_l;
	int		owner_l;
	int		group_l;
	int		size_l;

	i = 0;
	init_file_type(file_type);
	while (names->type != file_type[i] && file_type[i])
		i += 2;
	ft_printf("%c", file_type[i + 1]);
	print_perms(names->u_perm);
	print_perms(names->g_perm);
	print_perms(names->o_perm);
	link_l = give_length(ft_nbrlen(names->links), len->link_l);
	owner_l = give_length(ft_strlen(names->owner), len->user_l);
	group_l = give_length(ft_strlen(names->group), len->group_l);
	size_l = give_length(ft_nbrlen(names->size), len->size_l);
	ft_printf("%*d%*s", link_l, names->links, owner_l, names->owner);
	ft_printf("%*s%*lld", group_l, names->group, size_l, names->size);
	ft_printf(" %s ", names->mtime);
}

void	print_name(t_node *names, t_opt *options, t_length *len)
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

int	print_tree(t_node *names, t_opt *options, t_length *len)
{
	if (!names)
		return (0);
	if (names->left)
		print_tree(names->left, options, len);
	if ((names->name[0] != '.' || options->opt_a == 1))
		print_name(names, options, len);
	if (names->right)
		print_tree(names->right, options, len);
	return (1);
}

int	print_asked(DIR *directory, t_opt *options)
{
	struct dirent	*files;
	t_node			names;
	t_length		len;

	files = readdir(directory);
	len.name_l = 0;
	len.link_l = 0;
	len.user_l = 0;
	len.group_l = 0;
	len.size_l = 0;
	len.blocks = 0;
	if (!(add_elem(&names, files, &len, options)))
		return (0);
	while ((files = readdir(directory)))
		add_node(files, &names, options, &len);
	if (options->opt_l)
		ft_printf("total %lld\n", len.blocks);
	print_tree(&names, options, &len);
	if (!options->opt_l)
		ft_printf("\n");
	if (options->opt_R)
		print_recurs(&names, options);
	return (1);
}
