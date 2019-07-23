/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_csp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:37:12 by snunes            #+#    #+#             */
/*   Updated: 2019/06/28 12:11:00 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(t_flags *flag, va_list *ap)
{
	char			*espaces;
	unsigned char	c;
	int				espaces_len;
	int				len;

	espaces_len = 0;
	c = (unsigned char)va_arg(*ap, int);
	while (flag->width-- > 1)
		espaces_len++;
	len = espaces_len + 1;
	if (!(espaces = make_espaces(flag, espaces_len)))
		return (-1);
	if (!flag->minus)
		write(flag->fd, espaces, espaces_len);
	(c == '\0') ? write(flag->fd, "\0", 1) : write(flag->fd, &c, 1);
	if (flag->minus)
		write(flag->fd, espaces, espaces_len);
	free(espaces);
	return (len);
}

int	print_str(t_flags *flag, va_list *ap)
{
	int		i;
	char	*str;
	int		len;
	char	*espaces;

	espaces = NULL;
	i = 0;
	str = va_arg(*ap, char *);
	len = (!str) ? 6 : ft_strlen(str);
	flag->preci = (flag->preci < 0 || flag->preci > len) ? len : flag->preci;
	len = flag->preci;
	while (flag->width > len + i)
		i++;
	if (!(espaces = make_espaces(flag, i)))
		return (-1);
	if (!flag->minus)
		write(flag->fd, espaces, i);
	(!str) ? write(flag->fd, "(null)", len) : write(flag->fd, str, len);
	if (flag->minus)
		write(flag->fd, espaces, i);
	free(espaces);
	return (len + i);
}

int	print_ptr(t_flags *flag, va_list *ap)
{
	unsigned long int nb;

	nb = (unsigned long int)(va_arg(*ap, void *));
	return (print_unb(flag, nb, 16));
}
