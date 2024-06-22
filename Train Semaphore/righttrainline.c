#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

sem_t *rightline;
sem_t *leftline; 
//function prototype
int main() 
{ 
	int VALUE = 1;
	leftline = sem_open(name, O_CREAT, 0666, VALUE);	//if the semaphore has not been already created, create
	rightline = sem_open(name, O_CREAT, 0666, VALUE);
	int rightnum;
	int leftnum;
	for (int trains = 0; trains < 5; trains++) {
		sem_wait(rightline);
		printf("Right side of the track is now being used. Train #%d is passing through\n", trains + 1);
		sleep(1);
		rightnum++;
		sem_post(leftline);
	}
	printf("The total of %d trains have passed through the right side",trains + 1);

	sem_close(rightline);
    sem_unlink("rightline");	
	return 0; 
} 
