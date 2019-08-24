/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 14:15:57 by snunes            #+#    #+#             */
/*   Updated: 2019/08/24 14:17:56 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *old, char *new)
{
	free(old);
	old = NULL;
	if (!(old = ft_strdup(new)))
		return (NULL);
	return (old);
}
