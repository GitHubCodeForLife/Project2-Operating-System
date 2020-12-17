#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <time.h>
sem_t mutex; 
int x=0;
void* thread(void* arg) 
{  
	do{
		//printf("\n%d",x);
		sem_wait(&mutex);
		x=x+1;	
		//critical section 
		if(x==20)
		   x=0;
		sem_post(&mutex); 
		//usleep(100);
	}while(1);
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

