/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:33:35 by snunes            #+#    #+#             */
/*   Updated: 2019/04/27 11:38:10 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	convert;

	i = 0;
	convert = (unsigned char)c;
	while (len > i)
	{
		((unsigned char *)b)[i] = convert;
		i++;
	}
	return (b);
}
