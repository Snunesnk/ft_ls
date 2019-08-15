/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:17:17 by snunes            #+#    #+#             */
/*   Updated: 2019/08/15 12:00:15 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_perms(int perm)
{
	int i;

	i = 100;
	while (i > 0)
	{
		if ((perm / i) % 10 == 7)
			ft_printf("rwx");
		else if ((perm / i) % 10 == 6)
			ft_printf("rw-");
		else if ((perm / i) % 10 == 5)
			ft_printf("r-x");
		else if ((perm / i) % 10 == 4)
			ft_printf("r--");
		else if ((perm / i) % 10 == 3)
			ft_printf("-wx");
		else if ((perm / i) % 10 == 2)
			ft_printf("-w-");
		else if ((perm / i) % 10 == 1)
			ft_printf("--x");
		else if ((perm / i) % 10 == 0)
			ft_printf("---");
		i /= 10;
	}
}

void	print_info(t_node *node, t_length *len)
{
	char		file_type[20];
	int			i;
	int			link_l;
	int			owner_l;
	int			group_l;
	int			size_l;

	i = 0;
	init_file_type(file_type);
	while (node->type != file_type[i] && file_type[i])
		i += 2;
	ft_printf("%c", file_type[i + 1]);
	print_perms((node->u_perm * 10 + node->g_perm) * 10 + node->o_perm);
	link_l = give_length(ft_nbrlen(node->links), len->link_l);
	owner_l = give_length(ft_strlen(node->owner), len->user_l);
	group_l = give_length(ft_strlen(node->group), len->group_l);
	size_l = give_length(ft_nbrlen(node->size), len->size_l);
	ft_printf("%*d %-*s", link_l, node->links, owner_l, node->owner);
	ft_printf("  %-*s%*lld", group_l, node->group, size_l, node->size);
	ft_printf(" %s ", node->mtime);
}

void	print_name(t_node *node)
{
	char	*name;

	if (!(name = extract_name(node->name)))
		return ((void)ft_error("extract_name dans print_name a echoue"));
	if ((node->type == 4 && !IS_WRITEABLE(node->o_perm)))
		ft_printf("{B_cyan}%s", name);
	else if (node->type == 4 && IS_WRITEABLE(node->o_perm) && node->sp_bit == 1)
		ft_printf("{black}{H_green}%s", name);
	else if (node->type == 4 && IS_WRITEABLE(node->o_perm) && node->sp_bit != 1)
		ft_printf("{black}{H_yellow}%s", name);
	else if (node->type == 10)
		ft_printf("{purple}%s", name);
	else if (node->type == 7 && node->sp_bit == 0)
		ft_printf("{red}%s", name);
	else if (node->type == 12)
		ft_printf("{green}%s", name);
	else if (node->type == 1)
		ft_printf("{yellow}%s", name);
	else if (node->type == 2 || node->type == 0)
		ft_printf("{blue}{H_yellow}%s", name);
	else if (node->type == 6)
		ft_printf("{blue}{H_cyan}%s", name);
	else if (node->type == 7 && node->sp_bit == 4)
		ft_printf("{black}{h_red}%s", name);
	else if (node->type == 7 && node->sp_bit == 2)
		ft_printf("{black}{H_cyan}%s", name);
	else
		ft_printf("%s", name);
	free(name);
}

void	print_node(t_node *node, t_length *len)
{
	char		*name;

	if (!(name = extract_name(node->name)))
		return ((void)ft_error("extract name dans print node a echoue"));
	if (len->option & 4 && (name[0] != '.' || len->option & 8))
		print_info(node, len);
	if (name[0] != '.' || len->option & 8)
	{
		print_name(node);
		while (len->name_l > node->length++ && !(len->option & 4))
			write(1, " ", 1);
		if (len->option & 4)
			write(1, "\n", 1);
	}
	free(name);
}

void	print_tree(t_node *tree, char **path, t_length *len)
{
	char	*test;

	if (!tree)
		return ;
	if (tree->left)
		print_tree(tree->left, path, len);
	test = NULL;
	test = find_root(tree->name);
	if (!ft_strequ(*path, test))
	{
		if ((len->option & 48) && !(len->option & 64))
			ft_printf("\n");
		len->option = (len->option & 64) ? len->option ^ 64 : len->option;
		free(*path);
		*path = find_root(tree->name);
		if (len->multi > 1 || (len->multi == 1 && tree->type == 4))
			ft_printf("%.*s:\n", ft_strlen(*path) - 1, *path);
		if ((tree->links > 2) || (tree->type == 4 && (len->option & 8)))
			ft_printf("total %d\n", len->blocks);
	}
	print_node(tree, len);
	if (tree->right)
		print_tree(tree->right, path, len);
	free(test);
}
