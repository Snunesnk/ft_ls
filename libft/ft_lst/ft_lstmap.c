/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:23:35 by snunes            #+#    #+#             */
/*   Updated: 2019/04/24 12:24:07 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*start;

	if ((new_list = ft_lstnew(NULL, 0)) == NULL)
		return (NULL);
	new_list = f(lst);
	start = new_list;
	while (lst->next != NULL)
	{
		lst = lst->next;
		if (!(new_list->next = (t_list *)ft_memalloc(sizeof(t_list))))
		{
			free((void **)new_list);
			return (NULL);
		}
		new_list->next = f(lst);
		new_list = new_list->next;
	}
	return (start);
}
