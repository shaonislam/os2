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
#include <sys/ipc.h>
#include <sys/shm.h>


/*
1) allocate shared memory, use it, the deallocate it 
	-check all possible errors
2) master: fork off and exec one child and have child attach to shared memory
3) 
*/



int main (int argc, char *argv[])
{

	int option;


	int shm_id;
	key_t key;
	char *shm;

	key = 3456;
	shm_id = shmget(key, sizeof(int)*2, IPC_CREAT | 0666);

	if (shm_id == -1)
	{
		perror("shmget");
		exit(1);
	}
		
	shm = shmat(shm_id, NULL, 0);
	if (shm == (char * ) -1);
	{
		perror("shmat");
		exit(1);
	}		

	/* init clock : PUT THE CLOCK IN SHARED MEMORY 
	int* master_clock[2] = shm; */

	shmctl(shm_id, IPC_RMID, NULL);		 



	/* Create ONE test worker/kid */
	pid_t worker_pid = 0;
	worker_pid = fork();
	if (worker_pid == -1)
	{
		perror("fork ");
	{



        while((option = getopt(argc, argv, "hpn:")) != -1)
        {
                switch (option)
                        {
                        case 'h':
                                fprintf(stderr, "How it should run: ");
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


 
	return 0;


}


