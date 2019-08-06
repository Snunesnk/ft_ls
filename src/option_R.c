/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:21:31 by snunes            #+#    #+#             */
/*   Updated: 2019/08/06 17:43:28 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	up_a_dir(char *path, int nb)
{
	int i;
	int count;

	count = 0;
	i = ft_strlen(path);
	while (path && i >= 0 && count != nb)
	{
		i--;
		if (path[i] == '/')
			count++;
	}
	if (count == nb)
		path[i + 1] = '\0';
}

int	print_recurs(t_node *names, t_opt *options)
{
	if (!names)
		return (0);
	if (names->left)
		print_recurs(names->left, options);
	if ((names->name[0] != '.' || options->opt_a))
	{
		//ft_printf("Candidat read all: %s\n", names->name);
		if (!ft_strequ(names->name, ".\0") && !ft_strequ(names->name, "..\0")
				&& names->type == 4)
		{
			read_all(0, &(names->name), 1, options);
			up_a_dir(options->path, 2);
		}
	}
	if (names->right)
		print_recurs(names->right, options);
	return (1);
}
