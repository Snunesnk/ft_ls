/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:08:13 by snunes            #+#    #+#             */
/*   Updated: 2019/04/10 13:16:10 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (len > 0)
	{
		if (src[j] == '\0')
		{
			dst[i] = '\0';
			i++;
		}
		else
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		len--;
	}
	return (dst);
}
