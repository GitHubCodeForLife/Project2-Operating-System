#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <time.h>

void* MakeH(void* arg) {
	printf("H\n");
	pthread_detach(pthread_self()); 
}

void* MakeO(void* arg) {
	printf("O\n");
	pthread_detach(pthread_self()); 
}
void* MakeH2O(void* arg) {
	printf("=>H2O\n");
	pthread_detach(pthread_self()); 
}

int main() 
{ 
	pthread_t t1,t2,t3;
	while(1){
		pthread_create(&t1,NULL,MakeH,NULL);	 		
		pthread_create(&t2,NULL,MakeO,NULL);
		pthread_create(&t3,NULL,MakeH2O,NULL);  
	}
	return 0;
} 

