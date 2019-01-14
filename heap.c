#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "random.c"
int size = 1000000;
int numItems = 0;

/*
The root of the heap is always in array[1].
Its left child is in array[2].
Its right child is in array[3].
In general, if a node is in array[k], then its left child is in array[k*2], and its right child is in array[k*2 + 1].
If a node is in array[k], then its parent is in array[k/2] (using integer division, so that if k is odd, then the result is truncated; e.g., 3/2 = 1).
*/

void goUp(int *pq [],int position){

  if (position > 1) {
    //printf("child: %d, parrent: %d\n", pq[position], pq[(position )/2]);
    if(pq[position] < pq[(position)/2]){//If the child is larger than the parrent
      //printf("%d goes up, %d goes down\n", pq[position], pq[(position )/2]);
      int temp = pq[(position)/2];
      pq[(position)/2] = pq[position];
      pq[position] = temp;

      goUp(pq, (position/2));
    }else{
      //The child is smaller than its parent
    }
  }else{
    //The top
  }
}

void push(int *pq [], int priority){

  if (pq[1] == NULL) {
    pq[1] = priority;
    numItems++;
  }else{
    numItems++;
    pq[numItems] = priority;
    //Now we gotta compare with the parent
    //printf(" num %d\n", numItems);
    goUp(pq, numItems);

  }

}
void swap(int *pq [],int a, int b){
  int temp = pq[a];
  pq[a] = pq[b];
  pq[b] = temp;
}

void min_heapify (int *pq[ ] , int position)
{
int left  = 2*position;
int right = 2*position+1;
int min;
if(left <= numItems && pq[left] < pq[position] )
     min = left;
else
    min = position;
if(right <= numItems && pq[right] < pq[min] )
    min = right;
if(min != position)
{
    swap (pq,position,min);
    min_heapify (pq, min);
}
}

int pop(int *pq []){//Remove the root
  int root = pq[1];
  pq[1] = pq[numItems];
  pq[numItems] = NULL;
  numItems--;
  min_heapify(pq, 1);

  return root;

}

void printPQ(int *pq []){

  for (int i = 1; i < numItems+1; i++) {
    printf("%d ", pq[i]);
  }
  printf("\n");
}

void benchmarkHeap(int size){
  numItems = 0;

  int *pq[10000];
  pq[0] = NULL;

  for (int i = 0; i < 10000; i++) {
    pq[i] = NULL;
  }

  clock_t pushTotal, popTotal, findTotal;
  double pushWorst, pushBest, pushAvg;
  double popWorst, popBest, popAvg;
  double findWorst, findBest, findAvg;

  int once = 1;

  FILE *file = fopen("results.dat", "w");
  fprintf(file, "PUSH  FIND  POP\n");
  for (int j = 0; j < size; j++) {
    clock_t start_push = clock();
    for (int i = 0; i < 64; i++) {
      push(pq, randint(100)+1);
    }
    clock_t end_push = clock();
    clock_t time_push = end_push - start_push;
    pushTotal += time_push;
    fprintf(file, "%ld     ",pushTotal);

    if(once){
      pushWorst = time_push;
      pushBest = time_push;

    }else{
      if (time_push > pushWorst) {
        pushWorst = time_push;
      }
      if (time_push < pushBest) {
        pushBest = time_push;
      }
    }




    clock_t start_find = clock();
    for (int i = 0; i < 64; i++) {
      int a = pq[1];
    }
    clock_t end_find = clock();
    clock_t time_find = end_find - start_find;
    findTotal += time_find;
    fprintf(file, "%ld     ",findTotal);


    if(once){
      findWorst = time_find;
      findBest = time_find;

    }else{
      if (time_find > findWorst) {
        findWorst = time_find;
      }
      if (time_push < findBest) {
        findBest = time_find;
      }
    }



    clock_t start_pop = clock();
    for (int i = 0; i < 64; i++) {
      int a = pop(pq);
    }
    clock_t end_pop = clock();
    clock_t time_pop = end_pop - start_pop;
    popTotal += time_pop;
    fprintf(file, "%ld     ",popTotal);
    fprintf(file, "\n");


    if(once){
      popWorst = time_pop;
      popBest = time_pop;

    }else{
      if (time_pop > popWorst) {
        popWorst = time_pop;
      }
      if (time_pop < popBest) {
        popBest = time_pop;
      }
    }
    once = 0;
  }

  printf("asdasdas\n");
  fclose(file);

  pushAvg = pushTotal/size;
  popAvg = popTotal/size;
  findAvg = findTotal/size;
  FILE *bench = fopen("heapStats.dat", "w");
  fprintf(bench, "      PUSH  FIND  POP\n");
  fprintf(bench, "WORST  %d    %d    %d\n", (int)pushWorst, (int)findWorst, (int)popWorst);
  fprintf(bench, "BEST   %d    %d    %d\n", (int)pushBest, (int)findBest, (int)popBest);
  fprintf(bench, "AVG    %d    %d    %d\n", (int)pushAvg, (int)findAvg, (int)popAvg);
  fclose(bench);

}

void minHeapValidation(int * pq []){
  //We itterate through the whole array to check that the children is always larger than the parrent
  int yes = 0;
  int no = 0;


  int count = 2;
  while (pq[count] != NULL) {
    //printf("Is %d larger than/ equal with %d?\n", pq[count] , pq[count/2]);
    if(pq[count] >= pq[count/2]){
      yes++;
    }else{
      no++;
    }

    count++;
  }

  printf("True: %d, False: %d\n", yes, no);
}



int main(int argc, char **argv) {
	/*int *pq[size];
  pq[0] = NULL;
  //pq[1] = 2;
  for (int i = 0; i < size; i++) {
    pq[i] = NULL;
  }
  for (size_t i = 1; i < size-1; i++) {
    push(pq, (int)randint(10)+1);
  }
  minHeapValidation(pq);

  while (numItems > 0) {
    int a = pop(pq);
  }

  */
  benchmarkHeap(1000000);

  //printf("%d\n", pq[1]);
}
