/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <snunes@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:11:41 by root              #+#    #+#             */
/*   Updated: 2019/08/05 12:49:22 by snunes           ###   ########.fr       */
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
# include <time.h>

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
	int	user_l;
	int	group_l;
	int size_l;
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
	long long int	size;
	char			*mtime;
	struct s_node	*right;
	struct s_node	*left;
}				t_node;

char	*give_time(struct stat st);
void	update_l(t_length *len, t_node *node, t_opt *options);
int		give_length(int length, int to_reach);
int		organize_names(t_node *names, DIR *dir, t_opt *options, t_length *len);
void	read_all(int i, char **argv, int argc, t_opt *options);
void	init_file_type(char file_type[20]);

#endif
