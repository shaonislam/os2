/*  WORKER.C  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <getopt.h>
#include <sys/shm.h>
#include <sys/ipc.h>


int main (int argc, char *argv[])
{
	
	int add_time;
	add_time = atoi(argv[1]) * 1000000;
	
	int shm_id;
        key_t key;
        void* shm;	
        key = 3456;
        shm_id = shmget(key, sizeof(int)*2, IPC_CREAT | 0666);
        shm = shmat(shm_id, NULL, 0);
        int*  master_clock = shm;
	
	int i;
	for(i = 0; i < add_time; i++)
	{	
		master_clock[1] = master_clock[1] + 1;
	
		/*checking if milliseconds 'overflowed'*/		
		if (master_clock[1] == 999)
		{
			master_clock[0] = master_clock[0] + 1;
			master_clock[1] = 0;
		}

	}

	return 0;
}
