/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:26:26 by snunes            #+#    #+#             */
/*   Updated: 2019/05/04 18:05:13 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t			len;
	int				end;
	unsigned int	start;
	char			*str;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	end = (int)ft_strlen(s) - 1;
	while ((s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
													&& (end) >= (int)start)
		end--;
	len = end - start + 1;
	str = ft_strsub(s, start, len);
	return (str);
}
