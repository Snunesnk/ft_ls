/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:37:33 by snunes            #+#    #+#             */
/*   Updated: 2019/04/28 13:33:03 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		next;
	size_t		i;

	i = 0;
	next = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i + next] && next < len)
	{
		if (haystack[i + next] == needle[i])
		{
			while (haystack[i + next] == needle[i] && i + next < len)
			{
				i++;
				if (needle[i] == '\0')
					return ((char *)(haystack + next));
			}
			i = 0;
		}
		next++;
	}
	return (NULL);
}
