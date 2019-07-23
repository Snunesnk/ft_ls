/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:21:44 by snunes            #+#    #+#             */
/*   Updated: 2019/04/27 03:35:45 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		next;
	int		i;

	i = 0;
	next = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i + next])
	{
		if (haystack[i + next] == needle[i])
		{
			while ((haystack[i + next] == needle[i]) && needle[i])
			{
				i++;
			}
			if (needle[i] == '\0')
				return ((char *)(haystack + next));
			i = 0;
		}
		next++;
	}
	return (NULL);
}
