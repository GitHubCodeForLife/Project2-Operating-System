#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <time.h>
void* A1(void* arg) 
{ 
  	printf("\nA1"); 
} 
void* A2(void* arg) 
{ 
 	printf("\nA2"); 
} 
void* B1(void* arg) 
{ 
 	printf("\nB1"); 	
} 
void* B2(void* arg) 
{ 
 	printf("\nB2");
} 
int main()
{
	 pthread_t t1, t2, t3, t4;
	 pid_t pid;
	 pid = fork();
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
		pthread_create(&t3,NULL,B1,NULL); 
		pthread_create(&t4,NULL,B2,NULL);
		pthread_join(t3, NULL);
		pthread_join(t4, NULL); 
		break;
 	}
	exit(0);
	//return 0;
}

