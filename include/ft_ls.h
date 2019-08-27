/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <snunes@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:11:41 by root              #+#    #+#             */
/*   Updated: 2019/08/27 17:47:58 by snunes           ###   ########.fr       */
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
# include <sys/ioctl.h>

# define MAX(x, y) (x > y ? x : y)
# define IS_WRITEABLE(x) ((x) == 7 || (x) == 6 || (x) == 3 || (x) == 2)
# define IS_EXEC(x) ((x) == 7 || (x) == 5 || (x) == 3 || (x) == 1)

typedef struct	s_length
{
	int				option;
	int				name_l;
	int				link_l;
	int				user_l;
	int				group_l;
	int				size_l;
	long long int	blocks;
	int				column;
	int				written;
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

char			*adjust_time(char *time);
char			*creat_path(char *root, char *dir);
int				ft_filequ(char const *s1, char const *s2);
void			print_name(t_node *node, t_length *len);
void			print_info(t_node *node, t_length *len);
void			print_first(t_node *tree, t_length *len);
int				print_link(t_node *tree);
void			print_time(char *time);
void			print_dir(t_node *tree, t_length *len, int mode);
int				ft_tmpcmp(char *node_time, char *tree_time);
void			*ft_error(char *desc);
t_node			*recurs(t_node *tree, char *path, t_length *len);
int				requi(t_length *len, char *root, int mode);
void			free_tree(t_node *tree);
void			print_recurs(t_node *tree, t_length *len);
int				ft_node_cmp(t_node *node, t_node *new_node, t_length *len);
char			*extract_name(char *path);
t_node			*add_content(t_node *tree, char *name, t_length *len);
int				heigth(t_node *node);
int				check_balance(t_node *node);
t_node			*balance(int balanced, t_node *node, t_node *new_node, \
																t_length *len);
t_length		*init_len(t_length *len);
t_node			*add_node(t_node *tree, struct dirent *files, char *root, \
																t_length *len);
void			print_tree(t_node *tree, t_length *len);
void			update_l(t_node *node, t_length *len);
void			init_file_type(char file_type[20]);
int				give_length(int length, int to_reach);
t_node			*start_tree(t_node *tree, char *root, char *to_find);
char			*find_root(char *file);

#endif
