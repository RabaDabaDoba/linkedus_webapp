#include <stdio.h>
#include <stdlib.h>
#include "random.c"

typedef struct node {
    int priority;
    struct node* next;
} Node;

Node *createNode(int priority)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->priority = priority;
    node->next = NULL;
    return node;
}

int peek(Node** head)
{
    return (*head)->priority;
}

void pop(Node** head)
{
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

void push(Node** head, int p)
{
    Node* start = (*head);
    Node* temp = createNode(p);
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


void benchmarkPQ(int size){


  Node* pq = createNode(randint(20));

  clock_t pushTotal = 0;
  clock_t popTotal= 0;
  clock_t findTotal = 0;
  double pushWorst, pushBest, pushAvg;
  double popWorst, popBest, popAvg;
  double findWorst, findBest, findAvg;

  int once = 1;

  FILE *file = fopen("results.dat", "w");
  fprintf(file, "PUSH  FIND  POP\n");
  for (int j = 0; j < size; j++) {
    clock_t start_push = clock();
    for (int i = 0; i < 64; i++) {
      push(&pq, randint(100)+1);
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
      int a = peek(&pq);
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
      pop(&pq);
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
  FILE *bench = fopen("slStats.dat", "w");
  fprintf(bench, "      PUSH  FIND  POP\n");
  fprintf(bench, "WORST  %d    %d    %d\n", (int)pushWorst, (int)findWorst, (int)popWorst);
  fprintf(bench, "BEST   %d    %d    %d\n", (int)pushBest, (int)findBest, (int)popBest);
  fprintf(bench, "AVG    %d    %d    %d\n", (int)pushAvg, (int)findAvg, (int)popAvg);
  fclose(bench);

}




int main(int itterations, int max_priority)
{
  /*
  Node* pq = createNode(randint(20));

  for (size_t i = 0; i < 100; i++) {
      push(&pq, randint(20));
  }

  while (!isEmpty(&pq)) {
      printf("%d\n", pq->priority);
      pop(&pq);
  }
*/


  benchmarkPQ(1000000);
  return 0;
}







/*#include <stdio.h>
#include <stdlib.h>
#include "random.c"

typedef struct Node {
    int priority;
    struct Node* next;
} Node;

Node *createpq(int priority){
  Node *pq = (struct Node*)malloc(sizeof(struct Node));
  pq->priority = priority;
  pq->next = NULL;
  return pq;
}

int isEmpty(Node* head)
{
    return (head) == NULL;
}

void push(Node* head, int priority)
{
    Node* start = (head);
    Node* temp = createpq(priority);
    if ((head)->priority < priority) {
        temp->next = head;
        (head) = temp;
    }
    else {
        while (start->next != NULL &&
               start->next->priority < priority) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}


int pop(Node *pq){
  Node *child = pq->next;
  Node *temp = pq;
  pq = child;
  return temp->priority;

}


int main()
{

  Node *pq = createpq(2);
  printf("%d\n", pq->priority);
  push(pq, 0);
  printf("%d\n", pq->priority);
  push(pq, 1);
  printf("%d\n", pq->next->next->priority);

  return 0;
}
*/
