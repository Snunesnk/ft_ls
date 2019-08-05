/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 12:41:16 by snunes            #+#    #+#             */
/*   Updated: 2019/08/05 13:53:09 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <sys/stat.h>
#include "stdio.h"


int main(int argc, char **argv)
{
	int test;
	struct stat *buff;

	(void)argc;
	printf("argv[1] = %s\n", argv[1]);
	test = stat("argv[1]", buff);
	perror("stat()");
	printf("test = %d\n", test);
	printf("ID = %d\n", buff->st_dev);
	return (0);*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{

	struct stat sb;
	struct passwd *pwuser;
	struct group *grpnam;
	time_t	ltime;


	printf("test time : %ld\n", time(&ltime));
	printf("test ctime: %s\n", ctime(&ltime));
	if (argc < 2)
	{
			fprintf(stderr, "Usage: %s: file ...\n", argv[0]);
			exit(EXIT_FAILURE);
		}

	for (int i = 1; i < argc; i++)
	{
			if (-1 == stat(argv[i], &sb))
			{
						perror("stat()");
						exit(EXIT_FAILURE);
					}
	
			if (NULL == (pwuser = getpwuid(sb.st_uid)))
			{
						perror("getpwuid()");
						exit(EXIT_FAILURE);
					}
	
			if (NULL == (grpnam = getgrgid(sb.st_gid)))
			{
						perror("getgrgid()");
						exit(EXIT_FAILURE);
					}
	
			printf("%s:\n", argv[i]);
			printf("\tinode: %llu\n", sb.st_ino);
			printf("\towner: %u (%s)\n", sb.st_uid, pwuser->pw_name);
			printf("\tgroup: %u (%s)\n", sb.st_gid, grpnam->gr_name);
			printf("\tperms: %o\n", sb.st_mode);//(S_IRWXU | S_IRWXG | S_IRWXO)));
			printf("\tlinks: %d\n", sb.st_nlink);
			printf("\tsize: %lld\n", sb.st_size); /* you may use %lld */
			printf("\tatime: %s", ctime(&sb.st_atimespec.tv_sec));
			printf("\tmtime: %s", ctime(&sb.st_mtimespec.tv_sec));
			printf("\tctime: %s", ctime(&sb.st_ctimespec.tv_sec));
			printf("\ttaille block: %lld\n", sb.st_blocks);
			printf("\n");
		}

	return 0;
}
