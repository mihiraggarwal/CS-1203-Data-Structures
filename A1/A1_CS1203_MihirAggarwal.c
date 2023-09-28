#include <stdio.h>
#include <stdlib.h>
#define BADVAL -9999

// define node and nodeptr
struct node {
    int info;
    struct node *next;
};

typedef struct node * NODEPTR;

// define queue
struct queue {
    NODEPTR front, rear;
};

typedef struct queue QUEUE;

// function to create a node
NODEPTR createNode(int val) {
    NODEPTR p;
    p = (NODEPTR) malloc(sizeof(NODEPTR));
    p->info = val;
    p->next = NULL;
    return p;
}

// function to insert a value in the queue using the principles of linked lists
void insert(QUEUE *q, int val) {
    NODEPTR temp;
    temp = createNode(val);
    
    if (q->front == NULL) {
        q->front = temp;
        q->rear = temp;
    } else {
        (q->rear)->next = temp;
        q->rear = temp;
    }
}

// function to delete a value in the queue and return that using the principles of linked lists
int delete(QUEUE *q) {
    if (q->front == NULL) return BADVAL;

    NODEPTR temp;
    int val = (q->front)->info;
    temp = q->front;
    q->front = (q->front)->next;
    free(temp);

    if (q->front == NULL) q->rear = NULL;
    return val;
}

void print(QUEUE q) {
    NODEPTR temp;
    if (q.front == NULL) {
        printf("Queue empty\n");
        return;
    }
    printf("F -> ");
    for (temp = q.front; temp != NULL; temp = temp->next) {
        printf("%d ", temp->info);
    }
    printf("<- R\n");
}

int main() {
    QUEUE q;
    int menu, val;

    while (1) {
        printf("\n0. exit\n1. initialize\n2. delete\n3. insert\n4. print\nInput choice: ");
        scanf("%d", &menu);

        switch (menu) {
            case 0: exit(0);
            case 1: 
                q.front = q.rear = NULL;
                break;
            case 2:
                printf("Deleted element: %d\n", delete(&q));
                break;
            case 3:
                printf("Give element: ");
                scanf("%d", &val);
                insert(&q, val);
                printf("Inserted value %d\n", val);
                break;
            case 4:
                print(q);
                break;
        }
    }
}