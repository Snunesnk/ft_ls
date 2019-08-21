/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:00:18 by snunes            #+#    #+#             */
/*   Updated: 2019/08/21 13:15:11 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_node(t_node *node)
{
	if (node)
	{
		free(node->name);
		free(node->owner);
		free(node->group);
		free(node->mtime);
		free(node);
		node = NULL;
	}
}
