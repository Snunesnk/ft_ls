# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    all_test.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snunes <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/01 18:00:17 by snunes            #+#    #+#              #
#    Updated: 2019/09/01 18:04:18 by snunes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/sh

if [ -z $1 ]
then
	echo "ft_ls executable is missing"
	echo "Usage: ./all_test.sh path/to/ft_ls [p]"
	exit 1
fi

./basic_test.sh $1 $2
echo ""
./opt_l_test.sh $1 $2
