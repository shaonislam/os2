/*
Shaon Islam
CS 4760: Operating Systems
Project 2: Concurrent UNIX Proceses and Shared Memory
September 2018

master.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <getopt.h>



int main (int argc, char *argv[])
{

		/* init clock */
		milliseconds = 0;
		seconds = 0;


	        while((option = getopt(argc, argv, "hpn:")) != -1)
        {
                switch (option)
                        {
                        case 'h':
                                fprintf(stderr, "How it should run: ")
                                fprintf(stderr, "-n x: number of children to create\n");
                                fprintf(stderr, "-s x: indicate you many children should be allowed to exist in the system\n");
                                fprintf(stderr, "-h: display options to execute\n");
                                exit(1);
                        case 's':
				fprintf(stderr, "You have selected S\n");
				fprintf(stderr, "%s", optarg);
				break;
                        case 'n':
                                fprintf(stderr, "You have selected N\n");
                                break;
                        case '?':
                                fprintf(stderr, "Error\n");
                                break;
                        }
        }




}


