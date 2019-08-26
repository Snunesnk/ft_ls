/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:28:40 by snunes            #+#    #+#             */
/*   Updated: 2019/08/26 15:15:17 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_h_color(char color[10], t_flags *flag)
{
	char	*colours[20];
	int		i;

	init_hcolor(colours);
	i = 0;
	while (i < 20 && !ft_strequ(color, colours[i]))
		i += 2;
	if (i < 18)
		return (write(flag->fd, colours[i + 1], sizeof(colours[i + 1]) - 1));
	return (-1);
}

int	put_u_color(char color[10], t_flags *flag)
{
	char	*colours[18];
	int		i;

	init_ucolor(colours);
	i = 0;
	while (i < 18 && !ft_strequ(color, colours[i]))
		i += 2;
	if (i < 17)
		return (write(flag->fd, colours[i + 1], sizeof(colours[i + 1]) - 1));
	return (-1);
}

int	put_b_color(char color[10], t_flags *flag)
{
	char	*colours[18];
	int		i;

	init_bcolor(colours);
	i = 0;
	while (i < 18 && !ft_strequ(color, colours[i]))
		i += 2;
	if (i < 17)
		return (write(flag->fd, colours[i + 1], sizeof(colours[i + 1]) - 1));
	return (-1);
}

int	put_color(char color[10], t_flags *flag)
{
	char		*colours[20];
	int			i;

	init_color(colours);
	i = 0;
	while (i < 20 && !ft_strequ(color, colours[i]))
		i += 2;
	if (i < 19)
		return (write(flag->fd, colours[i + 1], sizeof(colours[i + 1]) - 2));
	return (-1);
}

int	handle_colors(t_flags *flag, const char *str)
{
	int		pos;
	int		ret;
	int		i;
	char	color[10];

	i = 0;
	pos = flag->spos + 1;
	ret = pos - 1;
	ft_bzero(color, 10);
	while (str[pos] != '}' && i < 8)
	{
		color[i++] = str[pos++];
		if (str[pos] != '}' && !ft_isalpha(str[pos]) && str[pos] != '_')
			return (ret);
	}
	if (color[0] == 'H' && put_h_color(color, flag) > 0)
		flag->color = 1;
	else if (color[0] == 'U' && put_u_color(color, flag) > 0)
		flag->color = 1;
	else if (color[0] == 'B' && put_b_color(color, flag) > 0)
		flag->color = 1;
	else if (put_color(color, flag) == -1)
		return (ret);
	flag->color = 1;
	return (pos + 1);
}
