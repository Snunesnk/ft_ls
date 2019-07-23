/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:07:51 by snunes            #+#    #+#             */
/*   Updated: 2019/05/02 12:40:08 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *s;

	if (!s1 || !s2)
		return (NULL);
	s = (char *)ft_memalloc(sizeof(*s) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	ft_strcpy(s, s1);
	s = ft_strcat(s, s2);
	return (s);
}
