#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <time.h>
void* A1(void* arg) 
{ 
  	printf("A1"); 
} 
void* A2(void* arg) 
{ 
 	printf("A2"); 
} 
void* B1(void* arg) 
{ 
 	printf("B1"); 	
} 
void* B2(void* arg) 
{ 
 	printf("B2");
} 
int main()
{
	 printf("\n");
	 pthread_t t1, t2;
	 pid_t pid;
	 pid = fork();// duplicates process
	 switch (pid)
	{
 	case -1:
	 	printf( "Khong the tao tien trinh con !" );
	 	exit(1);
 	case 0:
		pthread_create(&t1,NULL,A1,NULL); 
		pthread_create(&t2,NULL,A2,NULL); 
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		break;
 	default:
		pthread_create(&t1,NULL,B1,NULL); 
		pthread_create(&t2,NULL,B2,NULL);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL); 
		break;
 	}
 	printf("\n");
	exit(0);
	//return 0;
}

