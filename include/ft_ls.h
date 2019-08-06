/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <snunes@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:11:41 by root              #+#    #+#             */
/*   Updated: 2019/08/06 18:39:20 by snunes           ###   ########.fr       */
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

void	*singleton(int nb);

#endif
