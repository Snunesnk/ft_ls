/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:03:41 by snunes            #+#    #+#             */
/*   Updated: 2019/04/25 04:37:02 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char occur;

	occur = (char)c;
	while (*s)
	{
		if (*s == occur)
			return ((char *)s);
		s++;
	}
	if (occur == '\0')
		return ((char *)s);
	return (NULL);
}
