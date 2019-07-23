/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:03:08 by snunes            #+#    #+#             */
/*   Updated: 2019/05/03 17:28:49 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char **s1, char *s2, int mode)
{
	char *result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(*s1, s2);
	if (mode == 1)
		ft_strdel(s1);
	if (mode == 2)
		ft_strdel(&s2);
	if (mode == 3)
	{
		ft_strdel(s1);
		ft_strdel(&s2);
	}
	return (result);
}
