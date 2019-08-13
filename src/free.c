/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:00:18 by snunes            #+#    #+#             */
/*   Updated: 2019/08/13 19:26:53 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_node(t_node *node)
{
	free(node->name);
	free(node->owner);
	free(node->group);
	free(node->mtime);
	free(node);
}

void	free_len(t_length *len)
{
	while (len->prev)
		len = len->prev;
	while (len)
	{
		if (len->path)
			free(len->path);
		if (len->prev)
			free(len->prev);
		len = len->next;
	}
}
