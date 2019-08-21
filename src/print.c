/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:17:17 by snunes            #+#    #+#             */
/*   Updated: 2019/08/21 15:16:42 by snunes           ###   ########.fr       */
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
	int			group_l;
	int			size_l;

	i = 0;
	init_file_type(file_type);
	while (node->type != file_type[i] && file_type[i])
		i += 2;
	ft_printf("%c", file_type[i + 1]);
	print_perms((node->u_perm * 10 + node->g_perm) * 10 + node->o_perm);
	link_l = give_length(ft_nbrlen(node->links), len->link_l);
	i = give_length(ft_strlen(node->owner), len->user_l);
	group_l = give_length(ft_strlen(node->group), len->group_l);
	size_l = give_length(ft_nbrlen(node->size), len->size_l);
	ft_printf("%*d %-*s", link_l, node->links, i, node->owner);
	ft_printf("  %-*s%*lld", group_l, node->group, size_l, node->size);
	print_time(node->mtime);
}

int		print_sp(t_node *node, char *name)
{
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
	else
		return (0);
	return (1);
}

void	print_name(t_node *node, t_length *len)
{
	char	*name;

	name = NULL;
	if ((len->option & 64) && !ft_occur("./\0", node->name))
		name = ft_strdup(node->name);
	else
		name = extract_name(node->name);
	if (!name)
		return ;
	if (ft_strequ(node->name, "//etc\0"))
	{
		free(name);
		name = ft_strdup("/etc\0");
	}
	if (print_sp(node, name))
	{
		free(name);
		return ;
	}
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

void	print_tree(t_node *tree, t_length *len)
{
	char	*name;

	name = NULL;
	if (!tree)
		return ;
	if (tree->left)
		print_tree(tree->left, len);
	if (!(name = extract_name(tree->name)))
		return ;
	if (len->option & 4 && (name[0] != '.' || len->option & 8))
		print_info(tree, len);
	if (name[0] != '.' || len->option & 8)
	{
		if (!(len->option & 4) && len->written + len->name_l > len->column)
			len->written = write(1, "\n", 1) - 1;
		print_name(tree, len);
		len->written += len->name_l;
		if ((len->option & 4) && tree->type == 10)
			print_link(tree);
		while (len->name_l > tree->length++ && !(len->option & 4))
			write(1, " ", 1);
		if (len->option & 4)
			write(1, "\n", 1);
	}
	free(name);
	if (tree->right)
		print_tree(tree->right, len);
}
