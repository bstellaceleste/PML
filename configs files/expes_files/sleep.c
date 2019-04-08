#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(){

	struct timespec start, finish;
	double ns, seconds;
	int i=0,j;

	clock_gettime(CLOCK_MONOTONIC, &start);
	
	while(i<1000000) {i++;}
	clock_gettime(CLOCK_MONOTONIC, &finish);
        seconds = 1.0e9*finish.tv_sec - 1.0e9*start.tv_sec;
        ns = seconds + (finish.tv_nsec - start.tv_nsec);

//	do{
//		clock_gettime(CLOCK_MONOTONIC, &finish);
//		seconds = 1.0e9*finish.tv_sec - 1.0e9*start.tv_sec;
//   		ns = seconds + (finish.tv_nsec - start.tv_nsec);

//	}while(ns < 1000000000);
	printf("nanoseconds: %f\n", ns);
	return(0);
}
