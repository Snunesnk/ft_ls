/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprepend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:00:08 by snunes            #+#    #+#             */
/*   Updated: 2019/08/26 14:36:44 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strprepend(char *str, char *prepend)
{
	char	*buff;
	int		strlen;
	int		preplen;

	strlen = ft_strlen(str);
	preplen = ft_strlen(prepend);
	buff = NULL;
	if (!(buff = (char *)ft_memalloc(sizeof(char) * (strlen + preplen + 1))))
		return (NULL);
	buff = ft_strcat(buff, prepend);
	buff = ft_strcat(buff, str);
	return (buff);
}
