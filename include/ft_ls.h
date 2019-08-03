/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <snunes@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:11:41 by root              #+#    #+#             */
/*   Updated: 2019/08/03 17:45:26 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <stdio.h>

typedef struct	s_opt
{
	int opt_R;
	int opt_a;
	int opt_l;
	int opt_r;
	int opt_t;
	int	multi_dir;
}				t_opt;

typedef struct	s_length
{
	int	name_l;
	int	link_l;
}				t_length;

typedef struct	s_node
{
	char			*name;
	int				type;
	int				u_perm;
	int				g_perm;
	int				o_perm;
	int				length;
	int				links;
	char			*owner;
	char			*group;
	struct s_node	*right;
	struct s_node	*left;
}				t_node;

int		organize_names(t_node *names, DIR *dir, t_opt *options, t_length *len);
void	read_all(int i, char **argv, int argc, t_opt *options);
void	init_file_type(char file_type[20]);

#endif
