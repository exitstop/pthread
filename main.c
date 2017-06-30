#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


#include <sys/types.h>
#include <linux/unistd.h>
#include <sys/syscall.h>


pthread_mutex_t mut;

int sum=0;

// _syscall0(pid_t,gettid);

#define NUMMALLOC 15
 
typedef struct{
	int rowN; //номер обрабатываемой строки
	int rowSize; //размер строки
} pthrData;

//потоковая функция
void* threadFunc(void *thread_data){
	//завершаем поток
	pthrData *data = (pthrData*) thread_data;

	float r= (rand() %5)/10.0;
 	//printf("rand %f\n", r);

	pid_t tid;
    tid = syscall(SYS_gettid);    
 	// printf("start main %d\n", tid);

 	// while(){}
	pthread_mutex_lock(&mut);
		for(int i=0; i<5; i++){
	    	sum+=1;
	    	printf("Hello pthread %d getpid %d sum = %d \n",data->rowN, tid, sum);
	    	sleep(1.0+r);
	    }
    pthread_mutex_unlock(&mut);

	// for(int i=0; i<5; i++){
	
	
	// }


	pthread_exit(0);
}


 
int main(){
	

	
	

	// pid_t my_tid;
	// _syscall0( pid_t, gettid)
	// my_tid = gettid();

	pid_t tid;
    tid = syscall(SYS_gettid);    
 	printf("start main %d\n", tid);

 	time_t t;
 	srand((unsigned) time(&t));


	pthread_t* threads = (pthread_t*) malloc(NUMMALLOC * sizeof(pthread_t));
	pthrData* threadData = (pthrData*) malloc(NUMMALLOC * sizeof(pthrData));

	for(int i = 0; i < NUMMALLOC; i++){
		threadData[i].rowN = i;
		pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
	}

	for(int i = 0; i < NUMMALLOC; i++)
			pthread_join(threads[i], NULL);

	free(threads);
	free(threadData);

 

 
	return 0;
}