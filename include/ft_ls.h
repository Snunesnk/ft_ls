/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <snunes@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:11:41 by root              #+#    #+#             */
/*   Updated: 2019/08/03 11:42:24 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include <sys/stat.h>

typedef struct	s_opt
{
	int opt_R;
	int opt_a;
	int opt_l;
	int opt_r;
	int opt_t;
	int	multi_dir;
}				t_opt;

typedef struct	s_node
{
	char			*name;
	int				type;
	int				length;
	struct s_node	*right;
	struct s_node	*left;
}				t_node;

int		organize_names(t_node *names, DIR *directory, t_opt *options);
void	read_all(int i, char **argv, int argc, t_opt *options);

#endif
