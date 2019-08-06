/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <snunes@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:11:41 by root              #+#    #+#             */
/*   Updated: 2019/08/06 12:38:57 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ft_printf.h"
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

typedef struct	s_opt
{
	int		opt;
	int		multi_dir;
	char	*path;
}				t_opt;

typedef struct	s_length
{
	int				name_l;
	int				link_l;
	int				user_l;
	int				group_l;
	int				size_l;
	long long int	blocks;
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
	long long int	blocks;
	char			*mtime;
	struct s_node	*right;
	struct s_node	*left;
}				t_node;

int		print_recurs(t_node *names, t_opt *options);
void	read_all(int i, char **argv, int argc, t_opt *options);
int		add_node(struct dirent *files, t_node *names, t_opt *options, t_length *len);
int		add_elem(t_node *new_node, struct dirent *files, t_length *lem, 
															t_opt *options);
char	*give_time(struct stat st);
void	update_l(t_length *len, t_node *node, t_opt *options);
int		give_length(int length, int to_reach);
int		print_asked(DIR *directory, t_opt *options);
void	init_file_type(char file_type[20]);

#endif
