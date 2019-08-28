/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 11:59:55 by snunes            #+#    #+#             */
/*   Updated: 2019/08/28 19:10:57 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	t_flags	flag;
	int		len;
	int		(*func[17])(t_flags *flag, va_list *ap);

	flag.fd = fd;
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
		write(1, "\033[0m", sizeof("\033[0m"));
	va_end(ap);
	return (len);
}
