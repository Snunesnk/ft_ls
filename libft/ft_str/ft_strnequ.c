/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:40:49 by snunes            #+#    #+#             */
/*   Updated: 2019/04/28 15:03:10 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && (i + 1) < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i] && n != 0)
		return (0);
	return (1);
}
