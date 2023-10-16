#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define P 6
#define Q 6
#define U 3
int thread_count;
int M[P][Q];
int d[U];
int e[U];

void *Pth_mat_vect(void *rank){
	long my_rank = (long) rank;
	int i,j;
	int local_m = P/thread_count;
	int my_first_row = my_rank*local_m;
	int my_last_row = (my_rank +1) *local_m -1;
	
	for(i = my_first_row; i<=my_last_row;i++){
		e[i] = 0.0;
		for(j=0; j<Q; j++)
		e[i] += M[i][j]*d[j];
	}
	return NULL;
}

int main(int argc, char* argv[]){
	long thread;
	pthread_t* thread_handles;
	int i;
	d[0] = 1;
	d[1] = 2;
	d[2] = 3;
	for(i = 0; i<P; i++){
		for(int j=0; j<Q; j++)
			M[i][j] = 1+i;
	}
	thread_count = 3;
	thread_handles = malloc(thread_count*sizeof(pthread_t));
	for(thread = 0; thread<thread_count; thread++)
		pthread_create(&thread_handles[thread],NULL,Pth_mat_vect, (void *) thread);
	for (thread = 0; thread<thread_count; thread++){
		pthread_join(thread_handles[thread],NULL);
	}
	free(thread_handles);
	printf("\n");
	for(i = 0; i<Q; i++){
		printf("%d\n",e[i]);
	}
	return 0;
}