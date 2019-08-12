/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:06:08 by snunes            #+#    #+#             */
/*   Updated: 2019/08/12 18:09:03 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

int main(void)
{
	char buf[1024];
	ssize_t len;
	
	if ((len = readlink("/tmp", buf, sizeof(buf)-1)) != -1)
    	buf[len] = '\0';
	printf("test: %s\n", buf);
	return (0);
}
