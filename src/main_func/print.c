/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:17:17 by snunes            #+#    #+#             */
/*   Updated: 2019/09/02 12:59:26 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_perms(int perm, t_node *node)
{
	int i;

	i = 1000;
	while ((i /= 10))
	{
		((perm / i) % 10 > 3) ? ft_printf("r") : ft_printf("-");
		(IS_WRITEABLE((perm / i) % 10)) ? ft_printf("w") : ft_printf("-");
		if ((node->sp_bit & 1) && i < 10)
			(IS_EXEC((perm / i) % 10)) ? ft_printf("t") : ft_printf("T");
		else if (node->sp_bit & 2 && i == 10)
			(IS_EXEC((perm / i) % 10)) ? ft_printf("s") : ft_printf("S");
		else if (node->sp_bit & 4 && i == 100)
			(IS_EXEC((perm / i) % 10)) ? ft_printf("s") : ft_printf("S");
		else
			(IS_EXEC((perm / i) % 10)) ? ft_printf("x") : ft_printf("-");
	}
}

void	print_info(t_node *node, t_length *len)
{
	char		file_type[20];
	int			i;

	i = 0;
	init_file_type(file_type);
	while (node->type != file_type[i] && file_type[i])
		i += 2;
	ft_printf("%c", file_type[i + 1]);
	print_perms((node->u_perm * 10 + node->g_perm) * 10 + node->o_perm, node);
	ft_printf("%*d %-*s", len->link_l, node->links, len->user_l, node->owner);
	ft_printf(" %-*s", len->group_l, node->group);
	if (len->major)
	{
		if (node->major > -1)
			ft_printf("%*d, ", len->major, node->major);
		else
			ft_printf("%*s  ", len->major, "");
		ft_printf("%*d", 3, node->size);
	}
	else
		ft_printf("%*lld", len->size_l, node->size);
	print_time(node->mtime);
}

int		print_sp(t_node *node, char *name, t_length *len)
{
	if (!(len->option & 512) || node->type == 20)
	{
		if (node->type == 20)
			ft_dprintf(2, "ft_ls: %s: %s", name, node->path);
		else
			ft_printf("%s", name);
		return (1);
	}
	if ((node->type == 4 && !IS_WRITEABLE(node->o_perm)))
		ft_printf("{B_cyan}%s", name);
	else if (node->type == 4 && IS_WRITEABLE(node->o_perm) && node->sp_bit & 1)
		ft_printf("{black}{H_green}%s", name);
	else if (node->type == 4 && IS_WRITEABLE(node->o_perm) && node->sp_bit != 1)
		ft_printf("{black}{H_yellow}%s", name);
	else if (node->type == 10)
		ft_printf("{purple}%s", name);
	else if (node->type == 7 && node->sp_bit < 2)
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
	if ((len->option & 64) && !ft_occur("./\0", node->path) && node->type != 20)
	{
		free(node->name);
		node->name = ft_strdup(node->path);
	}
	if (!node->name)
		return ;
	if (ft_strequ(node->name, "//etc\0"))
	{
		free(node->name);
		node->name = ft_strdup("/etc\0");
	}
	if (print_sp(node, node->name, len))
		return ;
	else if ((node->type == 2 || node->type == 0))
		ft_printf("{blue}{H_yellow}%s", node->name);
	else if (node->type == 6)
		ft_printf("{blue}{H_cyan}%s", node->name);
	else if (node->type == 7 && node->sp_bit & 4)
		ft_printf("{black}{h_red}%s", node->name);
	else if (node->type == 7 && node->sp_bit & 2)
		ft_printf("{black}{H_cyan}%s", node->name);
	else
		ft_printf("%s", node->name);
}

void	print_tree(t_node *tree, t_length *len)
{
	if (!tree)
		return ;
	if (tree->left)
		print_tree(tree->left, len);
	if (len->option & 256 && (tree->name[0] != '.' || len->option & 8)
			&& tree->type != 20)
		print_info(tree, len);
	if (tree->name[0] != '.' || len->option & 8 || tree->type == 20)
	{
		if (!(len->option & 4) && len->written + len->name_l > len->column)
			len->written = write(1, "\n", 1) - 1;
		print_name(tree, len);
		len->written += len->name_l;
		if ((len->option & 256) && (tree->type == 10 || tree->changed))
			print_link(tree);
		while (len->name_l > tree->length++ && !(len->option & 4))
			write(1, " ", 1);
		if (len->option & 4)
			write(1, "\n", 1);
	}
	if (tree->right)
		print_tree(tree->right, len);
}
