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
		sem_wait(leftline);
		printf("Left side of the track is available to use. Train #%d is passing \n", trains + 1);
		sleep(1);
		leftnum++;
		sem_post(rightline);
	}
	printf("The total of %d trains have passed through the Left side\n",trains + 1);

	sem_close(leftline);
    sem_unlink("leftline");	
	return 0; 
} 