#include <pthread.h> 
#include <sys/stat.h>
#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <unistd.h>
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/wait.h>
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>       
sem_t sem1, sem2, sem3, sem4;
sem_t mutex;

void* MakeH(void* arg) {
	//Wait H20
	sem_wait(&sem4);
	printf("H\n");
	sem_post(&sem1);
	pthread_detach(pthread_self()); 
}
void* MakeO(void* arg) {
        //Wait H20
	sem_wait(&sem3);
	printf("O\n");
	sem_post(&sem2);
	pthread_detach(pthread_self()); 
}

void* MakeH2O(void* arg) {
	//mutex
	sem_wait(&mutex);

	sem_wait(&sem1);
	sem_wait(&sem1);
	sem_wait(&sem2);
	printf("=>H2O\n");
	printf("...\n");
	sleep(1);
	sem_post(&sem4);
	sem_post(&sem4);
	sem_post(&sem3);

	//post mutex
	sem_post(&mutex);
	pthread_detach(pthread_self()); 
	
}

int main() 
{ 
	int i;
	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);
	sem_init(&sem3, 0, 1);
	sem_init(&sem4, 0, 2);
	sem_init(&mutex, 0, 1);
	pthread_t t1,t2, t3;
	while(1){
		pthread_create(&t1,NULL,MakeH,NULL);
		pthread_create(&t2,NULL,MakeO, NULL);	
		pthread_create(&t3,NULL,MakeH2O,NULL); 
	}
	sem_destroy(&sem1);
	sem_destroy(&sem2);
	sem_destroy(&sem3);
	sem_destroy(&sem4);
	sem_destroy(&mutex); 
	return 0;
} 

