/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 04:34:49 by simon             #+#    #+#             */
/*   Updated: 2019/04/28 13:52:35 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (1);
	return (0);
}
