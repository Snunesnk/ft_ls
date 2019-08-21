/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 11:15:29 by snunes            #+#    #+#             */
/*   Updated: 2019/08/21 11:21:03 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strshift(char *str, int size)
{
	int		i;
	char	ret;

	i = 0;
	if (size < 0)
	{
		while (i < -1 * size)
		   str[i++]	= '\0';
	}
	while (str[i])
	{
		ret = str[i + size];
		str[i] = ret;
		i ++;
	}
	return (str);
}
