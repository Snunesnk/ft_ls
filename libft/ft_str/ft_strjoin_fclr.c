/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_fclr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:03:08 by snunes            #+#    #+#             */
/*   Updated: 2019/05/04 11:53:47 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin_fclr(char *s1, char *s2, int tofree, int toclr)
{
	char *result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	if ((tofree == 1 || tofree == 3))
		ft_strdel(&s1);
	if (tofree == 2 || tofree == 3)
		ft_strdel(&s2);
	if (toclr == 1 || toclr == 3)
		ft_strclr(s1);
	if (toclr == 2 || toclr == 3)
		ft_strclr(s2);
	return (result);
}
