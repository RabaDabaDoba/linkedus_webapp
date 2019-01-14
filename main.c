#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <sys/time.h>
#include "pq.c"


long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main()
{
  /*
    // Create a Priority Queue
    // 7->4->5->6
    Node* pq = createNode(4, 1);
    push(&pq, 5, 2);
    push(&pq, 6, 3);
    push(&pq, 7, 0);

    while (!isEmpty(&pq)) {
        printf("%d ", peek(&pq));
        pop(&pq);
    }
*/


    int itterations = 10; //2^n itterations
    int max_data = 100;
    int max_priority = 100;
/*
for (size_t i = 0; i < itterations + 1; i++) {
  clock_t start = clock();
  SLmain(pow(2,i), max_data, max_priority);
  clock_t end = clock();
  long int time_spent = (long int) (end - start);
  printf("Singele-linked list clock ticks: %ld, with %d itterations\n", time_spent,(int) pow(2,i));
}
*/

  FILE *file = fopen("pushBenchmark.dat", "w");

  for (int i = 1; i < 11; i++) {
    //BenchInfo *temp = pushBenchmark(pow(2,i), max_data, max_priority);
    //fprintf(file, "%d   %d   %d   %d   %d   \n", temp->itterations,temp->runtime,temp->best,temp->worst,(int) temp->average);
		int best = SLPushBestBenchmark(25*i, max_data, max_priority);
		int worst = SLPushWorstBenchmark(25*i, max_data, max_priority);
		int average = SLPushAverageBenchmark(25*i, max_data, max_priority);
		fprintf(file, "%d 	%d 	%d 	%d 	\n",512*25*i, best, worst, average);
		printf("%d\n", i);
  }
  fclose(file);

/*
double pushWorst, pushBest, pushAvg;
double popWorst, popBest, popAvg;
double findWorst, findBest, findAvg;
*/


    return 0;
}
