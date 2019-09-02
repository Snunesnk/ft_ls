# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    opt_l_test.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snunes <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/01 18:03:31 by snunes            #+#    #+#              #
#    Updated: 2019/09/02 15:56:33 by snunes           ###   ########.fr        #
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

echo "=========================== option rR tests ===========================\n";
mkdir -p .result;
mkdir -p level1/level{2..4}/level{5..9}
./$1 -1rR level1 > .result/r1 2>&1;
ls -1rR level1 > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1))
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -1rR] simple"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -1rR] simple"$pos$pos$tick$clear;
fi
rm -rf .result;
rm -rf level1;

mkdir -p .result;
mkdir -p tests;
mkdir -p tests/a tests/b tests/c;
mkdir -p tests/.a tests/.b tests/.c;
./$1 -1rR tests > .result/r1 2>&1;
ls -1rR tests > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -1rR] with hidden files"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -1rR] with hidden files"$pos$tick$clear;
fi
rm -rf .result;
rm -rf tests;

mkdir -p .result;
mkdir -p dir1 dir2 dir3;
chmod 000 dir1;
./$1 -1rR 2>&1 | grep -v denied> .result/r1 2>&1;
ls -1rR 2>&1 | grep -v denied > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": file without permission"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": file without permission"$pos$tick$clear;
fi
rm -rf .result;
chmod 777 dir1;
rm -rf dir1 dir2 dir3;

mkdir -p .result;
mkdir A;
touch  A/file rootFile;
./$1 -1rR A a rootfile Rootfile > .result/r1 2>&1;
ls -1rR A a rootfile Rootfile > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": Case insensitive test"$pos$cross$clear;
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
./$1 -1rR 2>&1 | grep -v denied | wc -l | tr -d ' ' | tr -d '\n' > .result/r1 2>&1;
ls -1rR 2>&1 | grep -v denied | wc -l | tr -d ' ' | tr -d '\n' > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": Count of error message"$pos$cross$clear;
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
mkdir -p dir/dir2;
touch dir/file1 dir/file2 dir/file3 dir/file4;
ln -s dir symdir;
./$1 -1rR symdir/ > .result/r1 2>&1;
ls -1rR symdir/ > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": Directories symlink"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": Directories symlink"$pos$tick$clear;
fi
rm -rf .result;
rm -rf dir;
rm -rf symdir;

mkdir -p .result;
echo $cyan"==========\ntime of [ft_ls -rR ~/]:"$clear;
time ./$1 -1rR ~/ | grep -v "ls:" > .result/r1 2>&1;
echo $cyan"==========\ntime of [ls -rR ~/]:"$clear;
time ls -1rR ~/ | grep -v "ls:" > .result/r2 2>&1;
echo $cyan"=========="$clear;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -1rR ~/]"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -1rR ~/]"$pos$tick$clear;
fi
rm -rf .result;

printf $Byellow"\nEnd of option rR tests\n"$clear;
if [ $success -eq $nb_test ]
then
	echo $green"Congratulation ! You passed all the tests."$clear;
else
	printf $cyan"%d test succeed, " "$success";
	((success= $nb_test - $success));
	printf "%d test failed\n"$clear "$success";
fi

echo "\n=========================== option rl tests ===========================\n";
mkdir -p .result;
./$1 -1rl > .result/r1 2>&1;
ls -1rl > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1))
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -1rl]"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -1rl]"$pos$pos$tick$clear;
fi
rm -rf .result;

mkdir -p .result;
./$1 -rl ../ > .result/r1 2>&1;
ls -rl ../ > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -rl ../]"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -rl ../]"$pos$tick$clear;
fi
rm -rf .result;

mkdir -p .result;
mkdir -p dir1 dir2 dir3;
./$1 -rl dir1 dir2 dir3 > .result/r1 2>&1;
ls -rl dir1 dir2 dir3 > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -rl dir1 dir2 dir3]"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -rl dir1 dir2 dir3]"$pos$tick$clear;
fi
rm -rf .result;
rm -rf dir1 dir2 dir3;

mkdir -p .result;
mkdir -p dir1 dir2 dir3;
touch  dir1/file1 dir2/file2 dir3/file3;
echo "Bonjour monde" > dir1/file1
echo "Hello world" > dir2/file2
echo "Hola mundo" > dir3/file3
./$1 -rl dir1 dir2 dir3 > .result/r1 2>&1;
ls -rl dir1 dir2 dir3 > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -rl dir1 dir2 dir3]"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -rl dir1 dir2 dir3]"$pos$tick$clear;
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
./$1 -rla dir > .result/r1 2>&1;
ls -rla dir > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": files with link"$pos$cross$clear;
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
ln -s dir dir/symdir;
echo "I like trains" > dir/sym1;
echo "2B3" > dir/sym2;
echo "Ah yes, enslaved words" > dir/sym3;
./$1 -rl dir > .result/r1 2>&1;
ls -rl dir > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": files with symlink"$pos$cross$clear;
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
./$1 -rl /dev | grep -v "ls:" | grep -v "dtrace" | grep -v "io8log" | grep -v "io8logtemp" > .result/r1 2>&1;
ls -rl /dev | grep -v "ls:" | grep -v "dtrace" | grep -v "io8log" | grep -v "io8logtemp" > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -rl /dev]"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -rl /dev]"$pos$tick$clear;
fi
rm -rf .result;

mkdir -p .result;
touch -t 999912312459 future;
touch -t 01010101 first_day;
touch -t 6901010101 past;
touch present;
touch present_too;
touch present_again;
./$1 -rl > .result/r1 2>&1;
ls -rl > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": special timestamps files"$pos$cross$clear;
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
./$1 -rl > .result/r1 2>&1;
ls -rl > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": setuid, setgid and sticky bit tests"$pos$cross$clear;
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

printf $Byellow"\nEnd of option rl tests\n"$clear;
if [ $success -eq $nb_test ]
then
	echo $green"Congratulation ! You passed all the tests."$clear;
else
	printf $cyan"%d test succeed, " "$success";
	((success= $nb_test - $success));
	printf "%d test failed\n"$clear "$success";
fi

echo "\n=========================== option ra tests ===========================\n";
mkdir -p .result;
mkdir tests;
mkdir -p tests/.hidden;
touch tests/.hide tests/not_hide;
./$1 -1ra tests > .result/r1 2>&1;
ls -1ra tests > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1))
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -1ra] simple"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -1ra] simple"$pos$pos$tick$clear;
fi
rm -rf .result;
rm -rf tests;

mkdir -p .result;
mkdir tests;
mkdir -p tests/.hidden{1..10} tests/not_hidden{1..10};
touch tests/.hide{1..10} tests/not_hide{1..10};
./$1 -1raR tests > .result/r1 2>&1;
ls -1raR tests > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1))
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -1raR] multiple dir"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -1raR] multiple dir"$pos$pos$tick$clear;
fi
rm -rf .result;
rm -rf tests;

printf $Byellow"\nEnd of option ra tests\n"$clear;
if [ $success -eq $nb_test ]
then
	echo $green"Congratulation ! You passed all the tests."$clear;
else
	printf $cyan"%d test succeed, " "$success";
	((success= $nb_test - $success));
	printf "%d test failed\n"$clear "$success";
fi

echo "\n=========================== Reverse basic tests ===========================\n";
mkdir -p result;
./$1 -r1 > result/r1 2>&1;
ls -r1 > result/r2 2>&1;
diff result/r1 result/r2 > result/r3;
	((nb_test+=1))
if [ -s result/r3 ]
then
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e result/r2;
	if [ -n $2 ] && [ "$2" == "p" ]
	then
		echo "\nDiff:";
		cat result/r3;
		echo "";
	fi
	echo $red"Test "$nb_test": [ft_ls -r1]"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -r1]"$pos$pos$tick$clear;
fi
rm -rf result;

mkdir -p result;
./$1 -r1 ../ > result/r1 2>&1;
ls -r1 ../ > result/r2 2>&1;
diff result/r1 result/r2 > result/r3;
	((nb_test+=1));
if [ -s result/r3 ]
then
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e result/r2;
	if [ -n $2 ] && [ "$2" == "p" ]
	then
		echo "\nDiff:";
		cat result/r3;
		echo "";
	fi
	echo $red"Test "$nb_test": [ft_ls -r1 ../]"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -r1 ../]"$pos$tick$clear;
fi
rm -rf result;

mkdir -p result;
mkdir -p dir1 dir2 dir3;
./$1 -r1 dir1 dir2 dir3 > result/r1 2>&1;
ls -r1 dir1 dir2 dir3 > result/r2 2>&1;
diff result/r1 result/r2 > result/r3;
	((nb_test+=1));
if [ -s result/r3 ]
then
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e result/r2;
	if [ -n $2 ] && [ "$1" == "p" ]
	then
		echo "\nDiff:";
		cat result/r3;
		echo "";
	fi
	echo $red"Test "$nb_test": [ft_ls -r1 dir1 dir2 dir3]"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -r1 dir1 dir2 dir3]"$pos$tick$clear;
fi
rm -rf result;
rm -rf dir1 dir2 dir3;

mkdir -p result;
mkdir -p dir1 dir2 dir3;
touch  dir1/file1 dir2/file2 dir3/file3;
./$1 -1 dir1 dir2 dir3 > result/r1 2>&1;
ls -1 dir1 dir2 dir3 > result/r2 2>&1;
diff result/r1 result/r2 > result/r3;
	((nb_test+=1));
if [ -s result/r3 ]
then
	echo $cyan"\n==========\nft_ls:"$clear;
	cat -e result/r1;
	echo $cyan"==========\nls:"$clear;
	cat -e result/r2;
	echo $cyan"=========="$clear;
	if [ -n $2 ] && [ "$2" = "p" ]
	then
		echo "\nDiff:";
		cat result/r3;
		echo "";
	fi
	echo $red"Test "$nb_test": [ft_ls -r1 dir1 dir2 dir3]"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -r1 dir1 dir2 dir3]"$pos$tick$clear;
fi
rm -rf result;
rm -rf dir1 dir2 dir3;

printf $Byellow"\nEnd of reverse basic tests\n"$clear;
if [ $success -eq $nb_test ]
then
	echo $green"Congratulation ! You passed all the tests."$clear;
else
	printf $cyan"%d test succeed, " "$success";
	((success=4-success));
	printf "%d test failed\n"$clear "$success";
fi

mkdir -p .result;
echo "=========================== option rt tests ===========================\n";
mkdir tests;
touch tests/a tests/b tests/c tests/d tests/e;
touch -t 201212101830.55 tests/c;
./$1 -1rt tests > .result/r1 2>&1;
ls -1rt tests > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1))
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -1rt] simple"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -1rt] simple"$pos$pos$tick$clear;
fi
rm -rf tests;

mkdir -p tests;
touch -t 201312101830.55 tests/a;
touch -t 201212101830.55 tests/b;
touch -t 201412101830.55 tests/c;
touch -t 202012101830.55 tests/d;
./$1 -1rt tests > .result/r1 2>&1;
ls -1rt tests > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -1rt] easy"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -1rt] easy"$pos$tick$clear;
fi
rm -rf tests;

mkdir -p tests;
touch -t 202012101830.55 tests/a;
touch -t 201312101830.55 tests/b;
touch -t 201412101830.55 tests/c;
touch -t 201411101830.55 tests/D;
touch -t 202011091830.55 tests/E;
touch -t 202012091730.55 tests/f;
touch -t 202012101729.55 tests/g;
touch -t 902012101729.55 tests/h;
./$1 -1rt tests 2>&1 > .result/r1 2>&1;
ls -1rt tests 2>&1 > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": [ft_ls -1rt] harder"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": [ft_ls -1rt] harder"$pos$tick$clear;
fi
rm -rf tests;

mkdir -p tests;
touch -t 200012101830.55 tests/a;
touch -t 201412101830.55 tests/b;
ln tests/b tests/d;
ln -s tests/c tests/e;
ln -s tests/a tests/f;
touch -t 4212101830.55 tests/c;
./$1 -1rt tests > .result/r1 2>&1;
ls -1rt tests > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": Test with symlink files"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": Test wit symlink files"$pos$tick$clear;
fi
rm -rf tests;

mkdir -p tests/level1{1..2}/level2{1..2}/level3{1..2};
touch -t 201212101830.55 tests/lvl1;
touch -t 201212101830.55 tests/level11/lvl11;
touch -t 201212101830.55 tests/level11/level21/lvl21;
touch -t 201212101830.55 tests/level11/level21/level31/lvl21;
./$1 -1trR > .result/r1 2>&1;
ls -1trR > .result/r2 2>&1;
diff .result/r1 .result/r2 > .result/r3;
	((nb_test+=1));
if [ -s .result/r3 ]
then
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
	echo $red"Test "$nb_test": Recursive with multiple dir"$pos$cross$clear;
else
	((success+=1));
	echo $green"Test "$nb_test": Recursive with multiple dir"$pos$tick$clear;
fi
rm -rf tests;

printf $Byellow"\nEnd of option t tests\n"$clear;
if [ $success -eq $nb_test ]
then
	echo $green"Congratulation ! You passed all the tests."$clear;
else
	printf $cyan"%d test succeed, " "$success";
	((success= $nb_test - $success));
	printf "%d test failed\n"$clear "$success";
fi
rm -rf .result
