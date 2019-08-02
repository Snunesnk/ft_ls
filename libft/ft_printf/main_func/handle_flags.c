/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 12:35:15 by snunes            #+#    #+#             */
/*   Updated: 2019/08/02 11:27:04 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*make_espaces(t_flags *flag, int len)
{
	char *str;

	if (len <= 0)
		len = 0;
	if (!(str = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (len--)
		str[len] = (flag->zero == 1) ? '0' : ' ';
	return (str);
}

char	*fill_nb_base(t_flags *flag, uintmax_t nbr, int base)
{
	int		len;
	char	*num;
	char	letter;

	letter = (flag->conv == 'x' || flag->conv == 'p') ? 'a' - 10 : 'A' - 10;
	len = ft_nblen(nbr, base);
	len = (flag->preci == 0 && !nbr) ? 0 : len;
	while (flag->preci > len)
		++len;
	if (!(num = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (len--)
	{
		num[len] = (nbr % base > 9) ? nbr % base + letter : nbr % base + 48;
		nbr /= base;
	}
	return (num);
}

int		fill_att(t_flags *flag, uintmax_t nb, char att[5])
{
	int	len;

	flag->nb = (nb == 0 && flag->preci) ? 0 : 1;
	flag->nb = (flag->preci > ft_nblen(nb, 8)) ? 0 : flag->nb;
	ft_bzero(att, 5);
	len = 0;
	if (flag->space && flag->sign > 0)
		att[len++] = ' ';
	if (flag->plus != 0 || flag->sign < 0)
		att[len++] = (flag->sign == -1) ? '-' : '+';
	if (flag->conv == 'p')
	{
		att[len++] = '0';
		att[len++] = 'x';
	}
	if (flag->diez == 1 && (flag->conv == 'o' || flag->conv == 'O') && flag->nb)
		att[len++] = '0';
	if (flag->diez && (flag->conv == 'x' || flag->conv == 'X') && nb)
		att[len++] = '0';
	if (flag->diez && flag->conv == 'x' && nb)
		att[len++] = 'x';
	if (flag->diez && flag->conv == 'X' && nb)
		att[len++] = 'X';
	return (len);
}
