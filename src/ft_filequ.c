/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:34:33 by snunes            #+#    #+#             */
/*   Updated: 2019/08/21 16:36:48 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_filequ(char const *s1, char const *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i] && s1[i] != '/')
			return (0);
		i++;
	}
	if (s1[i] != s2[i] && s1[i] != '/')
		return (0);
	return (1);
}
