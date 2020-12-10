#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <time.h>

int x=0;
void* thread(void* arg) 
{ 
	
	printf("\n Entered..\n"); 

	//critical section 
	do{
		//printf("\n%d",x);
		x=x+1;	
		if(x==20)
		   x=0;
		usleep(100);
	}while(1);
	
	//signal 
	printf("\nJust Exiting...\n"); 
	 
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
	
	exit(0);//Exit process PID = 0
} 
