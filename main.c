/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <snunes@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:37:27 by root              #+#    #+#             */
/*   Updated: 2019/07/23 13:47:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	DIR				*test;
	struct dirent	*names;
	int				all;
	int				arg;

	arg = argc;
	all = 0;
	while (arg > 0)
	{
		if (ft_strequ(argv[arg], "-a"))
			all = 1;
		arg--;
	}
	test = opendir(".");
	while ((names = readdir(test)))
	{
		if (!(names->d_name[0] == '.') || all == 1)
		{
			if (names->d_type == 4)
				ft_printf("{B_blue}%s  ", names->d_name);
			else
				ft_printf("%s  ", names->d_name);
		}
	}
	ft_printf("\n");
	closedir(test);
	return (0);
}
