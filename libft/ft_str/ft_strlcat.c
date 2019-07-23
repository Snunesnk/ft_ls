/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:30:45 by snunes            #+#    #+#             */
/*   Updated: 2019/04/25 13:48:31 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t srclen;
	size_t dstlen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen >= size)
		return (size + srclen);
	if (srclen < size - dstlen)
		ft_memcpy(dst + dstlen, src, srclen + 1);
	else
	{
		dst = dst + dstlen;
		while (size - dstlen - 1 > 0)
		{
			*dst = *src;
			dst++;
			src++;
			size--;
		}
		*dst = '\0';
	}
	return (dstlen + srclen);
}
