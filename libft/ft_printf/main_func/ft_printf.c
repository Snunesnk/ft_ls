/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 04:53:01 by snunes            #+#    #+#             */
/*   Updated: 2019/06/28 12:04:26 by snunes           ###   ########.fr       */
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

int	get_next_percent(const char *str, t_flags *flag)
{
	int		len;

	len = 0;
	if (flag->color == 1)
		write(1, "\033[0m", 5);
	ft_reset_flags(flag, 0);
	while (str[flag->spos] && str[flag->spos] != '%')
	{
		if (str[flag->spos] == '{')
			flag->spos = handle_colors(flag, str);
		len += (str[flag->spos] != '%') ? write(1, &str[flag->spos], 1) : 0;
		flag->spos += (str[flag->spos] == '%') ? 0 : 1;
	}
	if (!str[flag->spos + 1])
		flag->spos += 1;
	if (!str[flag->spos] && len == 0)
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
	va_end(ap);
	return (len);
}
