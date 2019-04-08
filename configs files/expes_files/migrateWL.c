#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <limits.h>

#define SIZE 51200
#define PERCENT 20
#define DUREE 300000000000
//#define DUREE 10000000000

struct page{
        unsigned long  entry[512];
};

void alloc_mem(struct page **data, void *buff){
	unsigned long i = 0;
	
        for(i = 0; i < SIZE; i++){
                data[i] = buff + (4096*i);
        }
}

int main(void){
        unsigned long i = 0, nbOps=0,nbWrite=0;
        int r, op=0;
	double ns=0, seconds;
	void *buff;
	time_t t;

        struct page *temp;
	struct timespec start, finish;
	clock_gettime(CLOCK_MONOTONIC, &start);
	do{
		
		i=0;
		posix_memalign(&buff, 4096, 4096*SIZE);
		srand((unsigned) time(&t));
		for(i = 0; i < SIZE; i++)
		{			
			temp=(buff + (4096*i));
			op=rand() % 100;
			if(op<PERCENT){
			        temp->entry[i%512] = i%512;
				nbWrite++;
			}	
			else
				r=temp->entry[i%512];
			clock_gettime(CLOCK_MONOTONIC, &finish);
			seconds = 1.0e9*finish.tv_sec - 1.0e9*start.tv_sec;
	   		ns = seconds + (finish.tv_nsec - start.tv_nsec);
			nbOps++;
			if(ns >= DUREE)
				break;
		}
       	        free(buff);
	}while(ns < DUREE);
	printf("----nbOPs=%ld-----percentWrite=%f\n",nbOps,(nbWrite*1.0/nbOps)*100);
}
