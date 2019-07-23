/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:01:50 by snunes            #+#    #+#             */
/*   Updated: 2019/07/23 12:04:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_all(t_flags *flag, char *esp, char *num, char att[5])
{
	int len;

	len = 0;
	if (flag->zero)
		len += write(flag->fd, att, ft_strlen(att));
	if (!flag->minus)
		len += write(flag->fd, esp, ft_strlen(esp));
	if (!flag->zero)
		len += write(flag->fd, att, ft_strlen(att));
	len += write(flag->fd, num, ft_strlen(num));
	if (flag->minus)
		len += write(flag->fd, esp, ft_strlen(esp));
	return (len);
}

int	print_nb(t_flags *flag, __intmax_t nb, int base)
{
	char	*num;
	char	*esp;
	char	att[5];
	int		len;
	int		esp_len;

	flag->sign = (nb < 0) ? -1 : 1;
	nb = (nb < 0) ? -nb : nb;
	flag->diez = (flag->preci > ft_nblen(nb, 8)) ? 2 : flag->diez;
	len = (flag->preci > ft_nblen(nb, base)) ? flag->preci : ft_nblen(nb, base);
	len = (flag->preci == 0 && !nb) ? 0 : len;
	esp_len = fill_att(flag, nb, att);
	esp_len = flag->width - (esp_len + len);
	if (!(num = fill_nb_base(flag, nb, base)))
		return (-1);
	if (!(esp = make_espaces(flag, esp_len)))
	{
		free(num);
		return (-1);
	}
	len = print_all(flag, esp, num, att);
	free(num);
	free(esp);
	return (len);
}

int	print_unb(t_flags *flag, __uintmax_t nb, int base)
{
	char	*num;
	char	*esp;
	char	att[5];
	int		len;
	int		esp_len;

	flag->diez = (flag->diez && flag->preci > ft_nblen(nb, 8)) ? 2 : flag->diez;
	flag->sign = 1;
	len = (flag->preci > ft_nblen(nb, base)) ? flag->preci : ft_nblen(nb, base);
	len = (flag->preci == 0 && !nb) ? 0 : len;
	esp_len = fill_att(flag, nb, att);
	esp_len = flag->width - (esp_len + len);
	if (!(num = fill_nb_base(flag, nb, base)))
		return (-1);
	if (!(esp = make_espaces(flag, esp_len)))
	{
		free(num);
		return (-1);
	}
	len = print_all(flag, esp, num, att);
	free(num);
	free(esp);
	return (len);
}

int	print_mant(t_flags *flag, char *mant)
{
	int	len;
	int	int_part;

	flag->diez = (flag->preci > 0) ? 1 : flag->diez;
	int_part = 0;
	len = ft_strlen(mant);
	while (mant[int_part] && mant[int_part] != '.')
		int_part++;
	int_part += ft_round(mant, flag->preci + int_part + 1);
	write(flag->fd, mant, int_part);
	while (mant[0] != '.' && mant[0])
		ft_shiftstr(mant, 2);
	ft_shiftstr(mant, 2);
	write(flag->fd, ".", 1);
	len = ft_strlen(mant);
	len = (flag->preci <= len) ? flag->preci : len;
	write(flag->fd, mant, len);
	flag->preci = flag->preci - len;
	while (flag->preci-- > 0)
		len += write(flag->fd, "0", 1);
	return (len + int_part + flag->diez);
}

int	print_double(t_flags *flag, char *mant, char *espaces, char *att)
{
	int len;
	int esp_len;
	int att_len;

	esp_len = 0;
	while (espaces[esp_len])
		esp_len++;
	att_len = 0;
	while (att[att_len])
		att_len++;
	len = 0;
	while (mant[len] && mant[len] != '.')
		len++;
	len++;
	if (flag->zero)
		write(flag->fd, att, att_len);
	if (!flag->minus)
		write(flag->fd, espaces, esp_len);
	if (!flag->zero)
		write(flag->fd, att, att_len);
	if ((len = print_mant(flag, mant)) == -1)
		return (-1);
	if (flag->minus)
		write(flag->fd, espaces, esp_len);
	return (len + esp_len + att_len);
}
