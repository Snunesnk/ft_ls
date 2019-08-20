/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 13:32:34 by snunes            #+#    #+#             */
/*   Updated: 2019/08/19 13:47:20 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	printf ("lines %d\n", w.ws_row);
	printf ("columns %d\n", w.ws_col);
	return 0;  // make sure your main returns int
}
