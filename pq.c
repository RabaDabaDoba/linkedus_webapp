#include <stdio.h>
#include <stdlib.h>
#include "random.c"

typedef struct node {
    int data;
    int priority;
    struct node* next;
} Node;

typedef struct benchInfo {
    int itterations;
    int runtime;
    int best;
    int worst;
    double average;
} BenchInfo;

Node *createNode(int data, int priority)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->priority = priority;
    node->next = NULL;
    return node;
}

int peek(Node** head)
{
    return (*head)->data;
}

void pop(Node** head)
{
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

void push(Node** head, int d, int p)
{
    Node* start = (*head);
    Node* temp = createNode(d, p);
    if ((*head)->priority > p) {
        temp->next = *head;
        (*head) = temp;
    }
    else {
        while (start->next != NULL &&
               start->next->priority < p) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}

int isEmpty(Node** head)
{
    return (*head) == NULL;
}

int SLmain(int itterations, int max_data, int max_priority)
{
  Node* pq = createNode(randint(max_data), randint(max_priority));

  for (size_t i = 0; i < itterations; i++) {
      push(&pq, randint(max_data), randint(max_priority));
  }

  while (!isEmpty(&pq)) {
      printf("%d\n", pq->priority);
      pop(&pq);
  }

  return 0;
}


int SLPushBenchmark(int itterations,int max_data, int max_priority){
  clock_t start, stop, runtime;

  start = clock();
  Node* pq = createNode(randint(max_data), randint(max_priority));
  for (size_t i = 0; i < itterations; i++) {
      push(&pq, randint(max_data), randint(max_priority));
  }
  stop = clock();
  runtime = stop - start;

  return runtime;
}

int SLPushAverageBenchmark(int itterations,int max_data, int max_priority){
  clock_t start, stop, runtime;
  int total, average;
  total = 0;

  for (int i = 0; i < itterations; i++) {
    start = clock();
    Node* pq = createNode(randint(max_data), randint(max_priority));
    for (size_t i = 0; i < 512; i++) {
        push(&pq, randint(max_data), randint(max_priority));
    }
    stop = clock();
    total += stop - start;

  }

  return total/(itterations);
}

int SLPushWorstBenchmark(int itterations,int max_data, int max_priority){
  clock_t start, stop, runtime;
  int worst = 0;


  for (int i = 0; i < itterations; i++) {
    start = clock();
    Node* pq = createNode(randint(max_data), randint(max_priority));
    for (size_t i = 1; i < 512; i++) {
        push(&pq, randint(max_data), randint(max_priority));
    }
    stop = clock();
    runtime = stop - start;

    if(worst < runtime){
      worst = runtime;
    }

  }

  return worst;
}

int SLPushBestBenchmark(int itterations,int max_data, int max_priority){
  clock_t start, stop, runtime;
  int best = 999999;


  for (int i = 0; i < itterations; i++) {
    start = clock();
    Node* pq = createNode(randint(max_data), randint(max_priority));
    for (size_t i = 1; i < 512; i++) {
        push(&pq, randint(max_data), randint(max_priority));
    }
    stop = clock();
    runtime = stop - start;

    if(best > runtime){
      best = runtime;
    }

  }

  return best;
}





BenchInfo *pushBenchmark(int itterations,int max_data, int max_priority){
  clock_t start, stop, runtime;
  int total, best, worst;
  double average;


  start = clock();
  Node* pq_1 = createNode(randint(max_data), randint(max_priority));
  for (size_t i = 0; i < itterations; i++) {
      push(&pq_1, randint(max_data), randint(max_priority));
  }
  stop = clock();
  runtime = stop - start;


/////////////////////////////////////



  start = clock();
  Node* pq_2 = createNode(randint(max_data), randint(max_priority));
  stop = clock();
  best = stop - start;
  worst = stop - start;
  average += best;

  int chunk = 64;

  for (size_t i = 0; i < itterations/64; i++) {
      start = clock();
      for (size_t i = 8; i < 64; i++) {
        push(&pq_2, randint(max_data), randint(max_priority));
      }
      stop = clock();

      if(best > stop-start){
        best = stop-start;
      }

      if(worst < stop-start){
        worst = stop-start;
      }

      average += stop-start;

  }

  average = average/(itterations + 1);

  BenchInfo* node = (BenchInfo*)malloc(sizeof(Node));
  node->itterations = itterations;
  node->runtime = runtime;
  node->best = best;
  node->worst = worst;
  node->average = average;

  //printf("%d  %d  %d  %d  %d", itterations,runtime,best,worst,(int) average);
  return node;
}
