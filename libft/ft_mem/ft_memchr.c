/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:13:21 by snunes            #+#    #+#             */
/*   Updated: 2019/04/24 18:29:10 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	chara;

	str = (unsigned char *)s;
	chara = (unsigned char)c;
	while (n--)
	{
		if (*str == chara)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
