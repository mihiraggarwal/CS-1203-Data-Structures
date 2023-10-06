#include <stdio.h>
#include <stdlib.h>

// define a BST node
struct bst_node {
    int key;
    struct bst_node *left;
    struct bst_node *right;
};

typedef struct bst_node * BST_NODEPTR;

// define a linked list node
struct ll_node {
    BST_NODEPTR key;
    struct ll_node *next;
};

typedef struct ll_node * LL_NODEPTR;

// define a stack
struct stack {
    LL_NODEPTR sp;
};

typedef struct stack STACK;

// create a BST node
BST_NODEPTR createBSTNode(int val) {
    BST_NODEPTR node;
    node = (BST_NODEPTR) malloc(sizeof(struct bst_node));
    node->key = val;
    node->left = node->right = NULL;
    return node;
}

// create a linked list node
LL_NODEPTR createLLNode(BST_NODEPTR bnode) {
    LL_NODEPTR ll_node;
    ll_node = (LL_NODEPTR) malloc(sizeof(struct ll_node));
    ll_node->key = bnode;
    ll_node->next = NULL;
    return ll_node;
}

// push a BST node to the stack
void push_stack(STACK *s, BST_NODEPTR bnode) {
    LL_NODEPTR node = createLLNode(bnode);
    if (s->sp == NULL) {
        s->sp = node;
    } else {
        node->next = s->sp;
        s->sp = node;
    }
}

// pop from the stack
void pop_stack(STACK *s) {
    LL_NODEPTR temp = (s->sp);
    s->sp = (s->sp)->next;
    free(temp);
}

// insert into a BST
BST_NODEPTR insert_bst(BST_NODEPTR node, int val) {
    BST_NODEPTR new = createBSTNode(val);

    if (node == NULL) {
        node = new;
        return node;
    }

    BST_NODEPTR check = node;
    BST_NODEPTR parent;
    int direction = 0;
    while (check != NULL) {
        if (val == check -> key) {
            printf("Value already exists");
            return node;
        }
        else if (val < check -> key) {
            parent = check;
            check = check -> left;
            direction = 0;
        } 
        else {
            parent = check;
            check = check -> right;
            direction = 1;
        }
    }
    if (direction == 0) {
        parent -> left = new;
    } else {
        parent -> right = new;
    }
    return new;
}

// run an iterative inorder traversal
void inorder(BST_NODEPTR node, STACK *s) {
    BST_NODEPTR temp = node;
    int left = 0;
    int popped = 0;

    // push the root node to the stack
    push_stack(s, temp);

    while (s -> sp != NULL) {
        if ((((s -> sp) -> key) -> left != NULL) && (left == 0)) {
            temp = temp -> left;
        }
        else {
            left = 0;

            // print in case left child doesn't exist
            printf("%d ", temp -> key);
            if (((s -> sp) -> key) -> right != NULL) {
                temp = temp -> right;
            }
            else {
                // if both left and right children don't exist, then pop
                pop_stack(s);
                if (s -> sp != NULL) temp = (s -> sp) -> key;
                popped = 1;
                left = 1;
            }
            // pop from the stack (after printing above) if left child doesn't exist and if not popped above
            if (popped == 0) pop_stack(s);
        }

        // if not popped, then push the next relavant value to the stack
        if (popped == 0) {
            push_stack(s, temp);
        }
        popped = 0;
    }
}

int main() {
    STACK st;
    st.sp = NULL;
    BST_NODEPTR node, temp;
    node = NULL;
    int c;
    int n;
    while (c != 0) {
        printf("Do you want to insert a number? (0 - no, 1 - yes): ");
        scanf("%d", &c);
        if (c == 1) {
            printf("Enter number to be inserted: ");
            scanf("%d", &n);
        } else break;
        if (node == NULL) {
            node = insert_bst(node, n);
        }
        else {
            temp = insert_bst(node, n);
        }
    }
    printf("Inorder traversal: ");
    if (node == NULL) printf("No elements found");
    else inorder(node, &st);
}