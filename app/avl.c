#include <stdio.h>
#include <string.h>

struct task {
    char to_do[30];
    char due_date[11];
    struct task *next;
};

// person data
struct node {
    char name[20];
    char surname[20];
    char birthdate[11];
    struct task *todo;
    int id;
    int height;
    struct node *left;
    struct node *right;
};

struct data {
    int size;
    struct node *data;
};

// AVL FUNCTIONS
int maximum(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int checkHeight(struct node *p) {
    if (p != NULL) {
        return p->height;
    }
    return 0;
}

void updateHeight(struct node *p) {
    int lef = 0;
    int rig = 0;
    if (p != NULL) {
        lef = checkHeight(p->left);
        rig = checkHeight(p->right);
        p->height = maximum(lef,rig) + 1;
    }
}

struct node *rotateLeft(struct node *p) {
    struct node *aux;
    if (p != NULL) {
        aux = malloc(sizeof(struct node));
        aux = p->right;
        p->right = aux->left;
        aux->left = p;
        updateHeight(p->left);
        updateHeight(p);
        return aux;
    }
}

struct node *rotateRight(struct node *p) {
    struct node *aux;
    if (p != NULL) {
        aux = malloc(sizeof(struct node));
        aux = p->left;
        p->left = aux->right;
        aux->right = p;
        updateHeight(p->right);
        updateHeight(p);
        return aux;
    }
}

struct node *doubleRotateLeft(struct node *p) {
    struct node *res;
    if (p != NULL) {
        res = malloc(sizeof(struct node));
        p->left = rotateLeft(p->left);
        res = rotateRight(p);
        return res;
    }
}

struct node *doubleRotateRight(struct node *p) {
    struct node *res;
    if (p != NULL) {
        res = malloc(sizeof(struct node));
        p->right = rotateRight(p->right);
        res = rotateLeft(p);
        return res;
    }
}

struct node *newAVL(struct node *p, int val, char *nam, char *snam, char *birth) {
    if (p == NULL) {
        p = malloc(sizeof(struct node));
        p->height = 1;
        p->left = NULL;
        p->right = NULL;
        p->todo = NULL;
        p->id = val;
        strcpy(p->name, nam);
        strcpy(p->surname, snam);
        strcpy(p->birthdate, birth);
        return p;
    } else {
        if (val < p->id) {
            p->left = newAVL(p->left, val, nam, snam, birth);
            if ((checkHeight(p->left) - checkHeight(p->right)) == 2) {
                if (val < p->left->id) {
                    p = rotateRight(p);
                } else {
                    p = doubleRotateRight(p);
                }
            }
            updateHeight(p);
        } else {
            p->right = newAVL(p->right, val, nam, snam, birth);
            if ((checkHeight(p->right) - checkHeight(p->left)) == 2) {
                if (val >= p->right->id) {
                    p = rotateLeft(p);
                } else {
                    p = doubleRotateLeft(p);
                }
            }
            updateHeight(p);
        }
        return p;
    }
}

// SYSTEM FUNCTIONS
int main() {
    struct data *head;
    head = malloc(sizeof(struct data));
    head->data = NULL;
    head->size = 0;
    // database examples
    int id = 1;
    char na[20] = "Ricardo";
    char sna[20] = "Costa";
    char bdate[11] = "1977-12-12";
    struct node *av;
    av = head->data;
    av = newAVL(av, id, na, sna, bdate);
    // first data called Ricardo Costa here...
    if (av != NULL) {
        printf("Found a first data: %d %s %s\n", av->id, av->name, av->surname);
    } else {
        printf("Cannot find first data in the database...\n");
    }
    // TODO more stuff soon, you can help it here :)
    return 0;
}