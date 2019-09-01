# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    opt_l_test.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snunes <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/01 18:03:31 by snunes            #+#    #+#              #
#    Updated: 2019/09/01 19:14:17 by snunes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/bash

clear="\033[0m"
green="\033[32m"
red="\033[31m"
cyan="\033[36m"
Byellow="\033[33;1m"
pos="\033[60G"
cross="\xE2\x9D\x8C"
tick="\xE2\x9C\x94"
success=0;
nb_test=0;

if [ -z $1 ]
then
	echo "ft_ls executable is missing"
	echo "Usage: ./b.sh path/to/ft_ls [p]"
	exit 1;
fi

echo "=========================== option l tests ===========================\n";
mkdir -p .result;
./$1 -1l > .result/r1 2>&1;
ls -1l > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1))
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": [ft_ls -1l]"$pos$cross$clear;
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e .result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e .result/r2;
	if [ -n $2 ] && [ "$2" == "p" ]
	then
		echo "\nDiff:";
		cat .result/r3;
		echo "";
	fi
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -1l]"$pos$pos$tick$clear;
fi
rm -rf .result;

mkdir -p .result;
./$1 -l ../ > .result/r1 2>&1;
ls -l ../ > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": [ft_ls -l ../]"$pos$cross$clear;
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e .result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e .result/r2;
	if [ -n $2 ] && [ "$2" == "p" ]
	then
		echo "\nDiff:";
		cat .result/r3;
		echo "";
	fi
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -l ../]"$pos$tick$clear;
fi
rm -rf .result;

mkdir -p .result;
mkdir -p dir1 dir2 dir3;
./$1 -l dir1 dir2 dir3 > .result/r1 2>&1;
ls -l dir1 dir2 dir3 > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": [ft_ls -l dir1 dir2 dir3]"$pos$cross$clear;
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e .result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e .result/r2;
	if [ -n $2 ] && [ "$1" == "p" ]
	then
		echo "\nDiff:";
		cat .result/r3;
		echo "";
	fi
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -l dir1 dir2 dir3]"$pos$tick$clear;
fi
rm -rf .result;
rm -rf dir1 dir2 dir3;

mkdir -p .result;
mkdir -p dir1 dir2 dir3;
touch  dir1/file1 dir2/file2 dir3/file3;
echo "Bonjour monde" > dir1/file1
echo "Hello world" > dir2/file2
echo "Hola mundo" > dir3/file3
./$1 -l dir1 dir2 dir3 > .result/r1 2>&1;
ls -l dir1 dir2 dir3 > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": [ft_ls -l dir1 dir2 dir3]"$pos$cross$clear;
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e .result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e .result/r2;
	echo $cyan"=========="$clear;
	if [ -n $2 ] && [ "$2" = "p" ]
	then
		echo "\nDiff:";
		cat .result/r3;
		echo "";
	fi
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -l dir1 dir2 dir3]"$pos$tick$clear;
fi
rm -rf .result;
rm -rf dir1 dir2 dir3;

mkdir -p .result;
mkdir -p dir;
touch dir/file ;
ln dir/file sym0;
ln dir/file sym1;
ln dir/file sym2;
ln dir/file sym3;
ln dir/file sym4;
ln dir/file sym5;
ln dir/file sym6;
ln dir/file sym7;
ln dir/file sym8;
ln dir/file sym9;
ln dir/file sym10;
ln dir/file sym11;
ln dir/file sym12;
./$1 -la dir > .result/r1 2>&1;
ls -la dir > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": files with link"$pos$cross$clear;
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e .result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e .result/r2;
	echo $cyan"=========="$clear;
	if [ -n $2 ] && [ "$2" = "p" ]
	then
		echo "\nDiff:";
		cat .result/r3;
		echo "";
	fi
else
	((success+=1));
	echo $green"Test "$nb_test": files with link"$pos$tick$clear;
fi
rm -rf .result;
rm -rf dir;
rm -rf sym0;
rm -rf sym1;
rm -rf sym2;
rm -rf sym3;
rm -rf sym4;
rm -rf sym5;
rm -rf sym6;
rm -rf sym7;
rm -rf sym8;
rm -rf sym9;
rm -rf sym10;
rm -rf sym11;
rm -rf sym12;

mkdir -p .result;
./$1 -l1 ../ > .result/r1 2>&1;
ls -l1 ../ > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": [ft_ls -l1 ../]"$pos$cross$clear;
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e .result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e .result/r2;
	echo $cyan"=========="$clear;
	if [ -n $2 ] && [ "$2" = "p" ]
	then
		echo "\nDiff:";
		cat .result/r3;
		echo "";
	fi
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -l1 ../]"$pos$tick$clear;
fi
rm -rf .result;

mkdir -p .result;
touch -t 999912312459 future;
touch -t 01010101 first_day;
touch -t 6901010101 past;
touch present;
touch present_too;
touch present_again;
./$1 -l > .result/r1 2>&1;
ls -l > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": special timestamps files"$pos$cross$clear;
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e .result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e .result/r2;
	echo $cyan"=========="$clear;
	if [ -n $2 ] && [ "$2" = "p" ]
	then
		echo "\nDiff:";
		cat .result/r3;
		echo "";
	fi
else
	((success+=1));
	echo $green"Test "$nb_test": special timestamps files"$pos$tick$clear;
fi
rm -rf .result;
rm -rf future;
rm -rf first_day;
rm -rf past;
rm -rf present;
rm -rf present_too;
rm -rf present_again;

mkdir -p .result;
touch setgid_exec; chmod 676 setgid_exec; chmod g+s setgid_exec;
touch setgid; chmod 666 setgid; chmod g+s setgid;
touch setuid_exec; chmod 766 setuid_exec; chmod u+s setuid_exec;
touch setuid; chmod 666 setuid; chmod u+s setuid;
touch sticky_exec; chmod 667 sticky_exec; chmod +t sticky_exec;
touch sticky; chmod 666 sticky; chmod +t sticky;
./$1 -l > .result/r1 2>&1;
ls -l > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": setuid, setgid and sticky bit tests"$pos$cross$clear;
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e .result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e .result/r2;
	echo $cyan"=========="$clear;
	if [ -n $2 ] && [ "$2" = "p" ]
	then
		echo "\nDiff:";
		cat .result/r3;
		echo "";
	fi
else
	((success+=1));
	echo $green"Test "$nb_test": setuid, setgid and sticky bit tests"$pos$tick$clear;
fi
rm -rf .result;
rm -rf setgid_exec;
rm -rf setgid;
rm -rf setuid_exec;
rm -rf setuid;
rm -rf sticky_exec;
rm -rf sticky;

printf $Byellow"\nEnd of option l tests\n"$clear;
if [ $success -eq $nb_test ]
then
	echo $green"Congratulation ! You passed all the tests."$clear;
else
	printf $cyan"%d test succeed, " "$success";
	((success= 4 - success));
	printf "%d test failed\n"$clear "$success";
fi
