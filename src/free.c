/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:00:18 by snunes            #+#    #+#             */
/*   Updated: 2019/08/20 18:58:28 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_node(t_node *node)
{
	if (node)
	{
		ft_printf("ca va free le name: %s\n", node->name);
		free(node->name);
		ft_printf("ca va free le owner\n");
		free(node->owner);
		ft_printf("ca va free le group\n");
		free(node->group);
		ft_printf("ca va free le time\n");
		free(node->mtime);
		ft_printf("ca va free la node\n");
		free(node);
		node = NULL;
	}
}
