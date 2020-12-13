#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <time.h>
sem_t mutex; 
int x=0;
void* thread(void* arg) 
{ 
	//wait 
	sem_wait(&mutex); 
	printf("\nP1: Entered..\n"); 

	//critical section 
	do{
		//printf("\n%d",x);
		x=x+1;	
		if(x==20)
		   x=0;
		//usleep(100);
	}while(1);
	
	//signal 
	printf("\nJust Exiting...\n"); 
	sem_post(&mutex); 
} 


int main() 
{ 
	sem_init(&mutex, 0, 1); 
	pthread_t t1,t2, t3; 
	pthread_create(&t1,NULL,thread,NULL); 
	pthread_create(&t2,NULL,thread,NULL); 
	
	//Wait
	while(x<100){
		printf("\nGia tri X: %d",x);
		//usleep(250);		
	}
	printf("\nX lon 100");
	pthread_detach(t1);
	pthread_detach(t2);
	sem_destroy(&mutex); 
	return 0;
} 

