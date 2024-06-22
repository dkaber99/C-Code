#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

sem_t *s; 		//a semaphore s

//function prototype
void* threadFunction(void* param); 

int main() 
{ 
	char *name = "my_semaphore";
	int VALUE = 3;
	//initialize semaphore to 1
	s = sem_open(name, O_CREAT, 0666, VALUE);	//if the semaphore has not been already created, create
	
	pthread_t t[7];
	int tnumber = 0;

	for (int i = 0; i < 7; i++) {
		pthread_create(&t[i], NULL, threadFunction, &tnumber);
    sleep(2);
		tnumber++;
	}

	for (int i = 0; i < 7; i++) {
		pthread_join(t[i], NULL);
	}
	
	printf("All Students have used the software\n");
	sem_close(s);
    sem_unlink(name);
	
	return 0; 
} 

void* threadFunction(void* param) 
{ 
	int tnum;
	tnum = *((int *)param);
	
	printf("\nStudent %d wants to use software license..\n", tnum);
	sem_wait(s); 			//can I access my critical section? (semWait())
	
	//critical section 
	printf("\nStudent %d has checked out a software license..\n", tnum);
  int randsleep;
	randsleep = rand() % 5;
	sleep(randsleep); 
	
	printf("\nStudent %d is checking his/her license back in..\n", tnum);
	
	sem_post(s); 		//signal that the thread is leaving and the CS is free (semSignal())
	
	pthread_exit(0);
}