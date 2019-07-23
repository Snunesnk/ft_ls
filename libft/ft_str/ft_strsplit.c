/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:47:59 by snunes            #+#    #+#             */
/*   Updated: 2019/04/28 15:40:05 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	int				new;
	unsigned int	start;
	int				i;
	char			**tab;

	new = 0;
	i = 0;
	if (!s)
		return ((char **)NULL);
	if (!(tab = (char **)ft_memalloc(sizeof(*tab) * ft_strlen(s) + 1)))
		return ((char **)NULL);
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			return (tab);
		start = i;
		while (s[i] != c && s[i])
			i++;
		tab[new] = ft_strsub(s, start, (i - start));
		new++;
	}
	return (tab);
}
