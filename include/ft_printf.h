/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:50:17 by snunes            #+#    #+#             */
/*   Updated: 2019/08/26 14:45:06 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_LLINT 1000000000000000000

typedef struct	s_flags
{
	int		diez;
	int		plus;
	int		space;
	int		minus;
	int		zero;
	int		width;
	int		preci;
	int		conv;
	int		sign;
	int		spos;
	int		nb;
	int		len;
	int		color;
	int		fd;
}				t_flags;

int				ft_dprintf(int fd, const char *format, ...);
int				print_double(t_flags *flag, char *mant, char *espaces,
																	char *att);
int				print_mant(t_flags *flag, char *mant);
int				print_percent(t_flags *flag);
int				get_next_percent(const char *str, t_flags *flag);
void			init_hcolor(char **colours);
void			init_ucolor(char **colours);
void			init_bcolor(char **colours);
void			init_color(char **colours);
void			init_dispatcher(int (*func[17])(t_flags *flag, va_list *ap));
int				print_all(t_flags *flag, char *esp, char *num, char *att);
int				handle_colors(t_flags *flag, const char*str);
int				create_l_doub(char *bits, char *mant);
int				handle_exept(t_flags *flag, int exept, int sign);
int				print_double(t_flags *flag, char *mant, char *espaces,
																	char *att);
int				create_doub(char *bits, char *mant);
int				fill_att(t_flags *flag, uintmax_t nbr, char *att);
char			*fill_nb_base(t_flags *flag, uintmax_t nbr, int base);
char			*make_espaces(t_flags *flag, int len);
int				ft_add(char *mantissa, char *two);
int				ft_multiply(char *buff);
void			ft_divide(char *buff);
void			ft_shiftstr(char *buff, int mode);
int				is_exept(char *mant, int exp);
int				ft_round(char *mant, int bound);
int				print_nb(t_flags *flag, intmax_t nb, int base);
int				get_j_int(t_flags *flag, va_list *ap);
int				get_uj_int(t_flags *flag, va_list *ap);
void			ft_reset_flags(t_flags *flag, int nb_flags);
int				print_unb(t_flags *flag, uintmax_t nb, int base);
void			order_flags(t_flags *flag);
int				get_flag(const char *str, t_flags *flag, va_list *ap);
int				get_uh_int(t_flags *flag, va_list *ap);
int				get_u_int(t_flags *flag, va_list *ap);
int				get_ul_int(t_flags *flag, va_list *ap);
int				get_ull_int(t_flags *flag, va_list *ap);
int				get_l_double(t_flags *flag, va_list *ap);
int				get_ll_int(t_flags *flag, va_list *ap);
int				get_l_int(t_flags *flag, va_list *ap);
int				get_h_int(t_flags *flag, va_list *ap);
int				get_hh_int(t_flags *flag, va_list *ap);
int				get_double(t_flags *flag, va_list *ap);
int				get_uhh_int(t_flags *flag, va_list *ap);
int				get_int(t_flags *flag, va_list *ap);
int				ft_printf(const char *format, ...);
int				print_char(t_flags *flag, va_list *ap);
int				print_str(t_flags *flag, va_list *ap);
int				print_ptr(t_flags *flag, va_list *ap);

#endif
