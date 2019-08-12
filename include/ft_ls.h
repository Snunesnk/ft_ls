/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <snunes@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:11:41 by root              #+#    #+#             */
/*   Updated: 2019/08/12 13:54:44 by snunes           ###   ########.fr       */
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

# define MAX(x, y) (x > y ? x : y)

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
	int				sp_bit;
	int				length;
	int				links;
	char			*owner;
	char			*group;
	long long int	size;
	long long int	blocks;
	char			*mtime;
	int				heigth;
	struct s_node	*right;
	struct s_node	*left;
}				t_node;

int			ft_node_cmp(t_node *tree, t_node *new_node, int mode);
int			heigth(t_node *node);
int			check_balance(t_node *node);
t_node		*balance(int balanced, t_node *node, t_node *new_node, int mode);
t_length	*init_len(t_length **len);
char		**sing_path(char *to_add);
void		print_files(t_node *tree, DIR *directory, char **path);
void		**singleton(int nb);
t_node		*add_node(t_node *tree, struct dirent *files, int mode, char *root);
void		print_tree(t_node *tree, int mode);
char		*give_time(struct stat st);
void		update_l(t_node *node);
void		init_file_type(char file_type[20]);
int			give_length(int length, int to_reach);
int			is_writeable(int perm);
t_node		*start_tree(t_node *tree, char *root, char *to_find);
char		*find_root(char *root, char *file);

#endif
