#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <time.h>
sem_t mutex1, mutex2, mutex3;
void* A1(void* arg) 
{ 
	sem_wait(&mutex2);
  	printf("A1");
	sem_post(&mutex2); 
} 
void* A2(void* arg) 
{ 
	 //wait 
    sem_wait(&mutex2);
 	printf("A2");
	sem_post(&mutex2);
	 
} 
void* B1(void* arg) 
{ 
	sem_wait(&mutex3);
 	printf("B1");
	sem_post(&mutex3);  	
} 
void* B2(void* arg) 
{ 
	sem_wait(&mutex3);
 	printf("B2");
	sem_post(&mutex3); 
} 
int main()
{
	 printf("\n");
     sem_init(&mutex1, 1, 1);
     sem_init(&mutex2, 0, 2);
	 sem_init(&mutex3, 0, 3);
	 pthread_t t1, t2;
	 pid_t pid;
	 pid = fork();
	 switch (pid)
	{
 	case -1:
	 	printf( "Khong the tao tien trinh con !" );
	 	exit(1);
 	case 0:
		//sem_wait(&mutex1);
		pthread_create(&t1,NULL,A1,NULL); 
		//sem_post(&mutex1);
		pthread_create(&t2,NULL,A2,NULL); 
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		break;
 	default:
		//sem_wait(&mutex1);
		pthread_create(&t1,NULL,B1,NULL); 
		//sem_post(&mutex1);
		pthread_create(&t2,NULL,B2,NULL);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL); 
		break;
 	}
 	printf("\n");
	sem_destroy(&mutex1);
	sem_destroy(&mutex2);
	sem_destroy(&mutex3);
	exit(0);
	//return 0;
}

