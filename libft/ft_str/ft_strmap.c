/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:12:37 by snunes            #+#    #+#             */
/*   Updated: 2019/04/28 15:07:47 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		i;

	if (!s || !f)
		return (NULL);
	i = 0;
	if (!(str = (char *)ft_memalloc(sizeof(*str) * ft_strlen(s) + 1)))
		return (NULL);
	while (s[i])
	{
		str[i] = (*f)(s[i]);
		i++;
	}
	return (str);
}
