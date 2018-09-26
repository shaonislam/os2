/* 

WORKER.C  


*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <getopt.h>
#include <sys/shm.h>
#include <sys/ipc.h>


int main (int argc, char *argv[])
{

	int multiplier;
	multiplier = atoi(argv[1]);	

	int shm_id;
        key_t key;
        void* shm;
	
        key = 3456;
        shm_id = shmget(key, sizeof(int)*2, IPC_CREAT | 0666);
        shm = shmat(shm_id, NULL, 0);

    
        int*  master_clock = shm;
	
	master_clock[0] = master_clock[0] + 50;
	master_clock[1] = master_clock[1] + 25;

	printf("Child's Clock: %d seconds, %d milliseconds\n", master_clock[0], master_clock[1]);       



	return 0;
}
