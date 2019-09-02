# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    opt_l_test.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snunes <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/01 18:03:31 by snunes            #+#    #+#              #
#    Updated: 2019/09/02 11:56:01 by snunes           ###   ########.fr        #
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

echo "=========================== option R tests ===========================\n";
mkdir -p .result;
mkdir -p level1/level{2..4}/level{5..9}
./$1 -1R level1 > .result/r1 2>&1;
ls -1R level1 > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1))
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": ft_ls -1R simple"$pos$cross$clear;
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
	echo $green"Test "$nb_test": ft_ls -1R simple"$pos$pos$tick$clear;
fi
rm -rf .result;
rm -rf level1;

mkdir -p .result;
mkdir -p tests;
mkdir -p tests/a tests/b tests/c;
mkdir -p tests/.a tests/.b tests/.c;
./$1 -1R tests > .result/r1 2>&1;
ls -1R tests > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": ft_ls -1R with hidden files"$pos$cross$clear;
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
	echo $green"Test "$nb_test": ft_ls -1R with hidden files"$pos$tick$clear;
fi
rm -rf .result;
rm -rf tests;

mkdir -p .result;
mkdir -p dir1 dir2 dir3;
chmod 000 dir1;
./$1 -1R 2>&1 | grep -v denied> .result/r1 2>&1;
ls -1R 2>&1 | grep -v denied > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": ft_ls -1R without permission"$pos$cross$clear;
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
	echo $green"Test "$nb_test": ft_ls -1R without permission"$pos$tick$clear;
fi
rm -rf .result;
chmod 777 dir1;
rm -rf dir1 dir2 dir3;

mkdir -p .result;
mkdir A;
touch  A/file rootFile;
./$1 -1R A a rootfile Rootfile > .result/r1 2>&1;
ls -1R A a rootfile Rootfile > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": Case insensitive test"$pos$cross$clear;
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
	echo $green"Test "$nb_test": Case insensitive test"$pos$tick$clear;
fi
rm -rf .result;
rm -rf A rootFile;

mkdir -p .result;
mkdir -p dir;
mkdir -p open/closed;
chmod 000 dir;
chmod 000 open/closed;
./$1 -1R 2>&1 | grep -v denied | wc -l | tr -d ' ' | tr -d '\n' > .result/r1 2>&1;
ls -1R 2>&1 | grep -v denied | wc -l | tr -d ' ' | tr -d '\n' > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": Count of error message"$pos$cross$clear;
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
	echo $green"Test "$nb_test": Count of error message"$pos$tick$clear;
fi
rm -rf .result;
chmod 777 dir;
chmod 777 open/closed;
rm -rf dir;
rm -rf open;

mkdir -p .result;
mkdir -p dir;
touch file1;
touch file2;
touch file3;
echo "YA PA D PANNO" > file1;
echo "To be or not to be" > file2;
echo "Stonks" > file3;
ln -s file1 dir/sym1;
ln -s file2 dir/sym2;
ln -s file3 dir/sym3;
echo "I like trains" > dir/sym1;
echo "2B3" > dir/sym2;
echo "Ah yes, enslaved words" > dir/sym3;
./$1 -l dir > .result/r1 2>&1;
ls -l dir > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
	echo $red"Test "$nb_test": files with symlink"$pos$cross$clear;
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
	echo $green"Test "$nb_test": files with symlink"$pos$tick$clear;
fi
rm -rf .result;
rm -rf dir;
rm -rf file1;
rm -rf file2;
rm -rf file3;

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
	((success= $nb_test - $success));
	printf "%d test failed\n"$clear "$success";
fi
