/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:02:53 by snunes            #+#    #+#             */
/*   Updated: 2019/08/17 14:22:56 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_strrev(char *to_reverse)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = 0;
	while (to_reverse[i])
		++i;
	--i;
	while (i > j)
	{
		tmp = to_reverse[j];
		to_reverse[j++] = to_reverse[i];
		to_reverse[i--] = tmp;
	}
}
