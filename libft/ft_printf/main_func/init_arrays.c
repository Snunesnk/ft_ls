/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arrays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:22:13 by snunes            #+#    #+#             */
/*   Updated: 2019/08/08 13:01:29 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_dispatcher(int (*func[17])(t_flags *flag, va_list *ap))
{
	func[0] = &print_char;
	func[1] = &print_str;
	func[2] = &print_ptr;
	func[3] = &get_hh_int;
	func[4] = &get_uhh_int;
	func[5] = &get_h_int;
	func[6] = &get_uh_int;
	func[7] = &get_l_int;
	func[8] = &get_ul_int;
	func[9] = &get_ll_int;
	func[10] = &get_ull_int;
	func[11] = &get_l_double;
	func[12] = &get_double;
	func[13] = &get_int;
	func[14] = &get_u_int;
	func[15] = &get_j_int;
	func[16] = &get_uj_int;
}

void	init_hcolor(char **colours)
{
	colours[0] = "H_black\0";
	colours[1] = "\033[40m\0";
	colours[2] = "H_red\0";
	colours[3] = "\033[41m\0";
	colours[4] = "H_green\0";
	colours[5] = "\033[42m\0";
	colours[6] = "H_yellow\0";
	colours[7] = "\033[43m\0";
	colours[8] = "H_blue\0";
	colours[9] = "\033[44m\0";
	colours[10] = "H_purple\0";
	colours[11] = "\033[45m\0";
	colours[12] = "H_cyan\0";
	colours[13] = "\033[46m\0";
	colours[14] = "H_gray\0";
	colours[15] = "\033[47m\0";
	colours[16] = "eoc\0";
	colours[17] = "\033[0m\0";
	colours[18] = "H_brown\0";
	colours[19] = "\033[0;43m\0";
}

void	init_ucolor(char **colours)
{
	colours[0] = "U_black\0";
	colours[1] = "\033[4;30m\0";
	colours[2] = "U_red\0";
	colours[3] = "\033[4;31m\0";
	colours[4] = "U_green\0";
	colours[5] = "\033[4;32m\0";
	colours[6] = "U_yellow\0";
	colours[7] = "\033[4;33m\0";
	colours[8] = "U_blue\0";
	colours[9] = "\033[4;34m\0";
	colours[10] = "U_purple\0";
	colours[11] = "\033[4;35m\0";
	colours[12] = "U_cyan\0";
	colours[13] = "\033[4;36m\0";
	colours[14] = "U_gray\0";
	colours[15] = "\033[4;37m\0";
	colours[16] = "eoc\0";
	colours[17] = "\033[0m\0";
}

void	init_bcolor(char **colours)
{
	colours[0] = "B_black\0";
	colours[1] = "\033[1;30m\0";
	colours[2] = "B_red\0";
	colours[3] = "\033[1;31m\0";
	colours[4] = "B_green\0";
	colours[5] = "\033[1;32m\0";
	colours[6] = "B_yellow\0";
	colours[7] = "\033[1;33m\0";
	colours[8] = "B_blue\0";
	colours[9] = "\033[1;34m\0";
	colours[10] = "B_purple\0";
	colours[11] = "\033[1;35m\0";
	colours[12] = "B_cyan\0";
	colours[13] = "\033[1;36m\0";
	colours[14] = "B_gray\0";
	colours[15] = "\033[1;37m\0";
	colours[16] = "eoc\0";
	colours[17] = "\033[0m\0";
}

void	init_color(char **colours)
{
	colours[0] = "black\0";
	colours[1] = "\033[30m\0";
	colours[2] = "red\0";
	colours[3] = "\033[31m\0";
	colours[4] = "green\0";
	colours[5] = "\033[32m\0";
	colours[6] = "yellow\0";
	colours[7] = "\033[33m\0";
	colours[8] = "blue\0";
	colours[9] = "\033[34m\0";
	colours[10] = "purple\0";
	colours[11] = "\033[35m\0";
	colours[12] = "cyan\0";
	colours[13] = "\033[36m\0";
	colours[14] = "gray\0";
	colours[15] = "\033[37m\0";
	colours[16] = "eoc\0";
	colours[17] = "\033[0m\0";
	colours[18] = "brown\0";
	colours[17] = "\033[0;33m\0";
}
