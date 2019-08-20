/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_occur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 12:22:36 by snunes            #+#    #+#             */
/*   Updated: 2019/08/20 14:56:52 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_occur(char *to_find, char *str)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (!to_find || !str)
		return (0);
	while (str[i] != to_find[0] && str[i])
		i++;
	while (str[i] == to_find[j] && to_find[j])
	{
		i++;
		j++;
	}
	if (!to_find[j])
		return (i);
	return (0);
}
