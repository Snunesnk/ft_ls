/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 04:53:01 by snunes            #+#    #+#             */
/*   Updated: 2019/08/28 19:17:00 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_percent(t_flags *flag)
{
	char	*espaces;
	int		espaces_len;
	int		len;

	espaces_len = 0;
	while (flag->width-- > 1)
		espaces_len++;
	len = espaces_len + 1;
	if (!(espaces = make_espaces(flag, espaces_len)))
		return (-1);
	if (!flag->minus)
		write(1, espaces, espaces_len);
	write(1, "%", 1);
	if (flag->minus)
		write(1, espaces, espaces_len);
	free(espaces);
	return (len);
}

int	get_next_percent(const char *str, t_flags *flg)
{
	int		len;
	int		ret;

	ret = 0;
	len = 0;
	if (flg->color == 1)
		write(flg->fd, "\033[0m", sizeof("\033[0m") - 1);
	ft_reset_flags(flg, 0);
	while (str[flg->spos] && str[flg->spos] != '%')
	{
		while (str[flg->spos] == '{')
		{
			flg->spos = handle_colors(flg, str);
			if (ret == flg->spos)
				flg->spos += write(1, &str[flg->spos], 1);
			ret = flg->spos;
		}
		len += (str[flg->spos] != '%') ? write(flg->fd, &str[flg->spos], 1) : 0;
		flg->spos += (str[flg->spos] == '%') ? 0 : 1;
	}
	if (!str[flg->spos + 1])
		flg->spos += 1;
	if (!str[flg->spos] && len == 0)
		return (-1);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_flags	flag;
	int		len;
	int		(*func[17])(t_flags *flag, va_list *ap);

	flag.fd = 1;
	init_dispatcher(func);
	ft_reset_flags(&flag, 1);
	len = 0;
	va_start(ap, format);
	while ((flag.len = get_next_percent(format, &flag)) >= 0)
	{
		len += flag.len;
		if ((flag.len = get_flag(format, &flag, &ap) - 1) >= 0 && flag.len < 17)
			len += (*func[flag.len])(&flag, &ap);
		else if (flag.len == 17)
			len += print_percent(&flag);
	}
	if (flag.color == 1)
		write(1, "\033[0m", sizeof("\033[0m") - 1);
	va_end(ap);
	return (len);
}
