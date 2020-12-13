#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <time.h>

sem_t sem1, sem2;

void* MakeH(void* arg) {
	//Wait H20
	printf("H\n");
	//post H
	sem_post(&sem2);
	pthread_exit(NULL);
}

void* MakeO(void* arg) {
	//Wait H20
	printf("O\n");
	//post O
	sem_post(&sem1);
	pthread_exit(NULL);
}
void* MakeH2O(void* arg) {
	//Wait 0
	sem_wait(&sem1);
	//Wait H
	sem_wait(&sem2);
	//Wait H
	sem_wait(&sem2);
	printf("=>H2O\n");
	printf("...\n");
	pthread_exit(NULL);
}

int main() 
{ 
	sem_init(&sem1, 0,0); 
	sem_init(&sem1, 0,0); 
	pthread_t t1,t2,t3;
	while(1){
		pthread_create(&t1,NULL,MakeH,NULL);		 			pthread_create(&t2,NULL,MakeO,NULL);
		pthread_create(&t3,NULL,MakeH2O,NULL); 
		//sleep(1);
	}
	sem_destroy(&sem1);
	sem_destroy(&sem2);  
	return 0;
} 

