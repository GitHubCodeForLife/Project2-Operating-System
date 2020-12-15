#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <time.h>

int x=0;
void* thread(void* arg) 
{ 
	//critical section 
	do{
		x=x+1;	
		if(x==20)
		   x=0;
		usleep(100);
	}while(1);
} 

int main() 
{ 
	pthread_t t1,t2;
	pthread_create(&t1,NULL,thread,NULL); 
	pthread_create(&t2,NULL,thread,NULL); 
	
	//Wait
	while(x<100){
		printf("\nValue of X: %d",x);
		usleep(50);		
	}
	printf("\nX lon hon 100");
	pthread_detach(t1);
	pthread_detach(t2);
	
	return 0;
} 

