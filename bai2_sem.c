#include <pthread.h> 
#include <sys/stat.h>
#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <unistd.h>
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/wait.h>
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */

void* A1(void* arg) 
{ 
  	printf("A1\n");
} 
void* A2(void* arg) 
{ 	
 	printf("A2\n"); 
} 
void* B1(void* arg) 
{ 
 	printf("B1\n");		
} 
void* B2(void* arg) 
{ 
 	printf("B2\n"); 
} 
int main()
{	
	 unsigned int value = 0;
	 int i;
	 sem_t *sem1, *sem2;
	 sem1 = sem_open ("pSem1", O_CREAT | O_EXCL, 0644, value); 
	 sem2 = sem_open ("pSem2", O_CREAT | O_EXCL, 0644, value);
   	 /* name of semaphore is "pSem", semaphore is reached using this name */
   	 sem_unlink ("pSem1");
	 sem_unlink ("pSem2");    
	 pthread_t t1, t2;
	 pid_t pid;

	  /* fork child processes */
	   for (i = 0; i < 2; i++){
		pid = fork ();
		if (pid < 0)              /* check for error      */
		    printf ("Fork error.\n");
		else if (pid == 0)
		    break;                  /* child processes */
	   }

	 if (pid != 0){
		/* wait for all children to exit */
		while (pid = waitpid (-1, NULL, 0)){
		    if (errno == ECHILD)
		        break;
		}

		printf ("\nParent: All children have exited.\n");
		
		/* cleanup semaphores */
		printf("sem_destroy return value:%d\n",sem_destroy (sem1));
		printf("sem_destroy return value:%d\n",sem_destroy (sem2));
		exit (0);
   	 }
    else{
	printf("Hello from process %d\n",i);
	if(i%2==0){
		//wait 
		printf("P %d is waiting...\n",i);
		pthread_create(&t1,NULL,A1,NULL); 
		pthread_join(t1, NULL);
		sem_post(sem1);	
		sem_wait(sem2);			
		pthread_create(&t2,NULL,A2,NULL); 
		pthread_join(t2, NULL);		
		
       		//sleep (1);
	} else{
		pthread_create(&t1,NULL,B1,NULL); 
		pthread_join(t1, NULL);
		
		sem_post(sem2);
		sem_wait(sem1);
		pthread_create(&t2,NULL,B2,NULL); 
		pthread_join(t2, NULL);
				
	}
        exit (0);		
       
   }
	
}

