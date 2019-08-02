/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 12:14:46 by snunes            #+#    #+#             */
/*   Updated: 2019/08/02 15:33:26 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_options(t_opt *options)
{
	options->opt_R = 0;
	options->opt_a = 0;
	options->opt_l = 0;
	options->opt_r = 0;
	options->opt_t = 0;
	options->multi_dir = 0;
}

int		get_options(int argc, char **argv, t_opt *options)
{
	int i;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		options->opt_R = ft_occur("R\0", argv[i]) ? 1 : options->opt_R;
		options->opt_a = ft_occur("a\0", argv[i]) ? 1 : options->opt_a;
		options->opt_l = ft_occur("l\0", argv[i]) ? 1 : options->opt_l;
		options->opt_r = ft_occur("r\0", argv[i]) ? 1 : options->opt_r;
		options->opt_t = ft_occur("t\0", argv[i]) ? 1 : options->opt_t;
		i++;
	}
	return (i);
}

int		main(int argc, char **argv)
{
	t_opt			options;
	int				arg;

	init_options(&options);	
	arg = get_options(argc, argv, &options);
	read_all(arg, argv, argc, &options);
	return (0);
}
