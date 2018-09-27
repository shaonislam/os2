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
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/wait.h>



void handle_terminate(int sig)
{
	fprintf(stderr, "Terminating due to 2 second program life span is over.\n");
	exit(1);
}

void handle_cntrlC(int sig){
	fprintf(stderr, "Terminating due to CNTRL-C\n");
	kill(0,SIGTERM);
	exit(1);
}


int main (int argc, char *argv[])
{
	/* set up signal */
	signal(SIGALRM, handle_terminate);
	signal(SIGINT, handle_cntrlC);

	int option, total_workers, worker_max;  

        while((option = getopt(argc, argv, "hs:n:")) != -1)
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
				worker_max = atoi(optarg);
				printf("Number of workers allowed to exist simultaneously: %d\n\n", worker_max);
				break;
                        case 'n':
				total_workers = atoi(optarg);
				if (total_workers > 20){
					fprintf(stderr, "Invalid Input: n can't be more than 20\n");
					exit(1);}
				printf("Total workers: %d\n", total_workers);
	                       	break;
                        case '?':
                                fprintf(stderr, "Error\n");
                                break;
                        }
        
	}

	


        int shm_id;
        key_t key;
        void* shm;
        key = 3456;

	/* Set Alarm to 2 seconds */
	alarm(2);

        shm_id = shmget(key, sizeof(int)*2, IPC_CREAT | 0666);

        if (shm_id == -1)
        {
                perror("shmget");
                exit(1);
        }
        shm = shmat(shm_id, NULL, 0);
    


        /* init clock : PUT THE CLOCK IN SHARED MEMORY */
        int*  master_clock = shm;  

	int seconds = 0;
	int milli = 0;

	master_clock[0] = seconds;
	master_clock[1] = milli;

        /* ARGUMENT TO PASS TO WORKER */
	char arg1[10];
	snprintf(arg1 , 10, "%d", total_workers);
        

	int i;


	
	
	total_workers = total_workers + 1;
	/* creates an s amount of workers  */
	for(i = 0; i < (total_workers - worker_max); i++)
	{
        	pid_t worker_pid = 0;
        	worker_pid = fork();
        	if (worker_pid == 0)
        	{
	        	/* trying to execute: worker x */
        		execlp("./worker", "./worker", arg1, (char *)NULL);
        		fprintf(stderr, "exec worked? \n");
        	}
	}		


	wait(NULL);

	int left_over;
	int remainder;
	if (master_clock[1] > 999)
	{
		left_over = master_clock[1] / 1000;
		master_clock[0] = master_clock[0] + left_over;
		remainder = master_clock[1] % 999;
		master_clock[1] = remainder;
	}


	fprintf(stderr, "\nMaster's Clock: %d seconds, %d milliseconds\n", master_clock[0], master_clock[1]);

        /*Dealloc the shared memory*/
        shmctl(shm_id, IPC_RMID, NULL);
 
	return 0;


}


