#include <stdio.h>  
#include <stdlib.h>  

// Deletion in the 2nd half of the file
   
struct Node  
{  
    int key;  
    struct Node *left;  
    struct Node *right;  
    int height;  
};  
   
int getHeight(struct Node *n){  
    if(n==NULL)  
        return 0;  
    return n->height;  
}  
   
struct Node *createNode(int key){  
    struct Node* node = (struct Node *) malloc(sizeof(struct Node));  
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1;  
    return node;  
}  

void displayTree(struct Node* root, int space)
{
    int i;

    if (root == NULL) return;

    space += 10;

    // Process right child first
    displayTree(root->right, space);

    // Print current node after space count
    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    // Process left child
    displayTree(root->left, space);
}
      
int maximum (int a, int b){  
    return (a>b)?a:b;  
}  
   
int getBalanceFactor(struct Node * n){  
    if(n==NULL){  
        return 0;  
    }  
    return getHeight(n->left) - getHeight(n->right);  
}  
   
struct Node* rightRotate(struct Node* y){  
    struct Node* x = y->left;  
    struct Node* T2 = x->right;  
   
    x->right = y;  
    y->left = T2;  
   
    x->height = maximum(getHeight(x->right), getHeight(x->left)) + 1;  
    y->height = maximum(getHeight(y->right), getHeight(y->left)) + 1;  
   
    return x;  
}  
   
struct Node* leftRotate(struct Node* x){  
    struct Node* y = x->right;  
    struct Node* T2 = y->left;  
   
    y->left = x;  
    x->right = T2;  
   
    x->height = maximum(getHeight(x->right), getHeight(x->left)) + 1;  
    y->height = maximum(getHeight(y->right), getHeight(y->left)) + 1;  
   
    return y;  
}  
   
struct Node *insert(struct Node* node, int key){  
    if (node == NULL)  
        return  createNode(key);  
   
    if (key < node->key)  
        node->left  = insert(node->left, key);  
    else if (key > node->key)  
        node->right = insert(node->right, key);  
   
    node->height = 1 + maximum(getHeight(node->left), getHeight(node->right));  
    int bf = getBalanceFactor(node);  
   
    // Left Left Case  
    if(bf>1 && key < node->left->key){  
        return rightRotate(node);  
    }  
    // Right Right Case  
    if(bf<-1 && key > node->right->key){  
        return leftRotate(node);  
    }  
    // Left Right Case  
    if(bf>1 && key > node->left->key){  
            node->left = leftRotate(node->left);  
            return rightRotate(node);  
        }  
    // Right Left Case  
    if(bf<-1 && key < node->right->key){  
            node->right = rightRotate(node->right);  
            return leftRotate(node);  
        }  
    return node;  
}

////////////////////////////////////////////////////////////////////////
// Assignment: Deletion of a node

// define a linked list node
struct ll_node {
    struct Node* key;
    struct ll_node *next;
};

typedef struct ll_node * LL_NODEPTR;

// define a stack
struct stack {
    LL_NODEPTR sp;
};

typedef struct stack STACK;

// create a linked list node
LL_NODEPTR createLLNode(struct Node* bnode) {
    LL_NODEPTR ll_node;
    ll_node = (LL_NODEPTR) malloc(sizeof(struct ll_node));
    ll_node->key = bnode;
    ll_node->next = NULL;
    return ll_node;
}

// push an AVL node to the stack
void push_stack(STACK *s, struct Node* bnode) {
    LL_NODEPTR node = createLLNode(bnode);
    if (s->sp == NULL) {
        s->sp = node;
    } else {
        node->next = s->sp;
        s->sp = node;
    }
}

// pop from the stack
struct Node* pop_stack(STACK *s) {
    LL_NODEPTR temp = (s->sp);
    s->sp = (s->sp)->next;
    // free(temp);
    return (temp->key);
}

// Deletion code
struct Node* delete(struct Node* node, int k) {
    struct Node* parent;
    struct Node* temp = node;
    int direction;

    STACK st;
    st.sp = NULL;

    if (node == NULL) {
        printf("Element not found\n");
        return NULL;
    }

    // findNode
    // assumption - the key of each node is unique
    while (temp->key != k) {
        push_stack(&st, temp);
        parent = temp;
        (temp -> height)--;

        if ((temp -> right == NULL) && (temp -> left == NULL)) {
            printf("Element not found\n");
            return NULL;
        }

        if (k < temp->key) {
            temp = temp->left;
            direction = 0;
        }
        else {
            temp = temp -> right;
            direction = 1;
        }
    }

    // deleteNode
    // 0 children
    if (temp->left == NULL && temp->right == NULL) {
        if (direction == 0) parent->left = NULL;
        else parent->right = NULL;
    }

    // 1 child
    else if (temp -> left == NULL) {
        if (direction == 0) parent -> left = temp -> right;
        else parent -> right = temp -> right;
    }
    
    else if (temp -> right == NULL) {
        if (direction == 0) parent -> left = temp -> left;
        else parent -> right = temp -> left;
    }

    // 2 children
    else {
        // inorder successor
        int d2 = 1;
        struct Node* inparent = temp;
        struct Node* intemp = temp -> right;

        push_stack(&st, temp);
        
        while (intemp -> left != NULL) {
            inparent = intemp;
            intemp = intemp -> left;
            d2 = 0;
        }

        int val = intemp -> key;
        intemp -> key = temp -> key;
        temp -> key = val;

        // post swap - 0 children
        if (intemp->right == NULL) {
            if (d2 == 0) inparent -> left = NULL;
            else inparent -> right = NULL;
        }

        // post swap - 1 child (right)
        else {
            if (d2 == 0) inparent -> left = intemp -> right;
            else inparent -> right = intemp -> right;
        }
    }

    // balanceTree
    while (st.sp != NULL) {
        struct Node* chp = pop_stack(&st);
        int bf = getBalanceFactor(chp);
        
        int bfl, bfr;
        if (chp -> left != NULL) bfl = getBalanceFactor(chp -> left);
        if (chp -> right != NULL) bfr = getBalanceFactor(chp -> right);

        // Left Left Case  
        if(bf>1 && bfl>0){  
            return rightRotate(chp);  
        }  
        // Left Right Case  
        else if(bf>1 && bfr<0){  
            chp->left = leftRotate(chp->left);  
            return rightRotate(chp);  
        }  

        // Right Right Case  
        if(bf<-1 && bfr<0){  
            return leftRotate(chp);  
        }  
        // Right Left Case  
        else if(bf<-1 && bfl>0){  
            chp->right = rightRotate(chp->right);  
            return leftRotate(chp);  
        }  
    }
    return node;
}

////////////////////////////////////////////////////////////////////////
   
void preOrder(struct Node *root)  
{  
    if(root != NULL)  
    {  
        printf("%d ", root->key);  
        preOrder(root->left);  
        preOrder(root->right);  
    }  
}  

void inOrder(struct Node *root)  
{  
    if(root != NULL)  
    {  
        inOrder(root->left);  
        printf("%d ", root->key);  
        inOrder(root->right);  
    }  
}  
   
int main(){  
    struct Node * root = NULL;  

    int menu;
    while(1){
        printf("0. exit, 1. insert, 2. delete, 3. preorder, 4. inorder, 5. print. Input Choice: ");
        scanf("%d", &menu);

	    switch(menu){
	        case 0: exit(0);
            case 1: printf("Give element to insert: "); 
                    int elm;
                    scanf("%d", &elm); 
                    root = insert(root, elm); 
                    break;
            case 2: printf("Give element to delete: "); 
                    int elm2;
                    scanf("%d", &elm2); 
                    root = delete(root, elm2); 
                    break;
            case 3: preOrder(root);
                    break;
            case 4: inOrder(root);
                    break;
            case 5: displayTree(root, 0); 
                    break;
	        default: printf("Wrong choice\n");
        }
    }
   
    return 0;  
}  
