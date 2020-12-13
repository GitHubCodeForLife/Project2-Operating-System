#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SNAME1 "/mysem1"
#define SNAME2 "/mysem2"
sem_t mutex1, mutex2;
void* A1(void* arg) 
{ 
  	printf("A1");
	//post A2
	sem_post(&mutex1);
	//Post B2
	sem_t* sem1 = (sem_t*) arg;
	sem_post(sem1);
} 
void* A2(void* arg) 
{ 	
	//Wait A1
        sem_wait(&mutex1);
	//Wait B1
        sem_t* sem2 = (sem_t*) arg;
	sem_wait(sem2);
			
 	printf("A2"); 
} 
void* B1(void* arg) 
{ 
 	printf("B1");
	//Post B2
	sem_post(&mutex2);
	//Post A2
	sem_t* sem2 = (sem_t*) arg;
	sem_post(sem2);
			
} 
void* B2(void* arg) 
{ 
	//Wait B1
	sem_wait(&mutex2);
	//Wait A1
	sem_t* sem1 = (sem_t*) arg;
	sem_wait(sem1);
 	printf("B2"); 
} 
int main()
{
	 printf("\n");
	 sem_init(&mutex1, 0, 0);
	 sem_init(&mutex1, 0, 0);
	 sem_t *sem1, *sem2;
	 //sem_init(sem1, 1, 0);
	 //sem_init(sem2, 1, 0);
	 pthread_t t1, t2, t3, t4;
	 pid_t pid;
	 pid = fork();
	 switch (pid)
	{
 	case -1:
	 	printf( "Khong the tao tien trinh con !" );
	 	exit(1);
 	case 0:
		printf("\n");
		sem1 = sem_open(SNAME1, 0);
	 	sem2 = sem_open(SNAME2, 0);
		pthread_create(&t1,NULL,A1,(void*)&sem1); 
		pthread_create(&t2,NULL,A2,(void*)&sem2); 
		pthread_join(t2, NULL);
		pthread_join(t1, NULL);
		break;
 	default:
		printf("\n");
		sem1 = sem_open(SNAME1, 0);
	 	sem2 = sem_open(SNAME2, 0);
		pthread_create(&t3,NULL,B1,(void*)&sem2);
		pthread_create(&t4,NULL,B2,(void*)&sem1);
		pthread_join(t4, NULL); 
		pthread_join(t3, NULL);
		break;
 	}
 	printf("\n");
	sem_destroy(&mutex1);
	sem_destroy(&mutex2);
	exit(0);
	//return 0;
}

