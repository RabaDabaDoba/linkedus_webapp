typedef struct node {
    int data;
    int priority;
    struct node* next;
} Node;
Node *createNode(int data, int priority);
int peek(Node** head);
void pop(Node** head);
void push(Node** head, int d, int p);
int isEmpty(Node** head);
