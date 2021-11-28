#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// global variavels
int person_id = 0;

// task data
struct task {
    char to_do[50];
    char duedate[11];
    char duetime[10];
    struct task *next;
};

// person data
struct node {
    char name[20];
    char surname[20];
    char birthdate[11];
    int tsize;
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
        p->tsize = 0;
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

// STAFF FUNCTIONS
void addPeople(struct node *p) {
    char nam[20];
    char snam[20];
    char bdate[20];
    printf("Digite Nome e Sobrenome: ");
    scanf("%s %s", &nam, &snam);
    printf("Digite a Data de Nascimento: ");
    scanf("%s", &bdate);
    person_id++;
    p = newAVL(p, person_id, nam, snam, bdate);
    printf("Pessoa Criada com Sucesso.\n");
}

void addTask(struct node *p, int id, char *tname, char *ddate, char *dtime) {
    if (p != NULL) {
        if (p->id == id) {
            struct task *ntask;
            ntask = malloc(sizeof(struct task));
            strcpy(ntask->to_do, tname);
            strcpy(ntask->duedate, ddate);
            strcpy(ntask->duetime, dtime);
            ntask->next = p->todo;
            p->todo = ntask;
            p->tsize++;
        } else {
            addTask(p->left, id, tname, ddate, dtime);
            addTask(p->right, id, tname, ddate, dtime);
        }
    }
}

int removeTask(struct node *p, int id, char *tname) {
    int res = 0;
    if (p != NULL) {
        if (p->id == id) {
            struct task *o;
            struct task *prev;
            prev = NULL;
            o = p->todo;
            while (o != NULL) {
                if (strcmp(o->to_do, tname) == 0) {
                    if (prev == NULL) {
                        p->todo = o->next;
                    } else {
                        prev->next = o->next;
                    }
                    p->tsize--;
                    if (p->tsize == 0) {
                        p->todo = NULL;
                    }
                    free(o);
                    res = 1;
                    break;
                } else {
                    prev = o;
                    o = o->next;
                }
            }
        } else {
            res = removeTask(p->left, id, tname);
            res = removeTask(p->right, id, tname);
        }
    }
    return res;
}

void printTask(struct task *p) {
    if (p != NULL) {
        printf("To-Do: %s Date: %s at %s\n", p->to_do, p->duedate, p->duetime);
        printTask(p->next);
    }
}

void checkTask(struct node *p, int id) {
    if (p != NULL) {
        if (p->id == id) {
            if (p->todo != NULL) {
                printTask(p->todo);
            }
        } else {
            checkTask(p->left, id);
            checkTask(p->right, id);
        }
    }
}

int checkPerson(int id, struct node *p, char typ) {
    int res = 0;
    if (p != NULL) {
        if (p->id == id) {
            if (typ == 'P') {
                printf("===== PEOPLE INFORMATION =====\n");
                printf("ID: %d\nName: %s %s\nBirth Date: %s\n", p->id, p->name, p->surname, p->birthdate);
                printf("Tasks:");
                if (p->todo != NULL) {
                    printf("\n");
                    checkTask(p, p->id);
                } else {
                    printf(" None\n");
                }
            }
            res = 1;
        } else {
            res = checkPerson(id, p->left, typ);
            res = checkPerson(id, p->right, typ);
        }
    }
    return res;
}

// DAYLIST FUNCTIONS
void printPeople(struct node *p) {
    if (p != NULL) {
        printf("%d\t%s %s\t%s\t%d Tasks\n", p->id, p->name, p->surname, p->birthdate, p->tsize);
        printPeople(p->left);
        printPeople(p->right);
    }
}

void showAllPersons(struct node *p) {
    printf("========== PERSONAS ==========\n");
    printPeople(p);
}

void savePerson(FILE *fp, struct node *p) {
    if (p != NULL) {
        fprintf(fp, "%d %s %s %s\n", p->id, p->name, p->surname, p->birthdate);
        savePerson(fp, p->left);
        savePerson(fp, p->right);
    }
}

void saveTask(FILE *fp, struct node *p) {
    if (p != NULL) {
        struct task *o;
        o = p->todo;
        if (o != NULL) {
            while (o != NULL) {
                fprintf(fp, "%d %s %s %s\n", p->id, o->to_do, o->duedate, o->duetime);
                o = o->next;
            }
        }
        saveTask(fp, p->left);
        saveTask(fp, p->right);
    }
}

// SYSTEM FUNCTIONS
int main() {
    struct data *head;
    head = malloc(sizeof(struct data));
    head->data = NULL;
    head->size = 0;
    struct node *av;
    av = head->data;
    // Read Person Data File
    printf("Loading Person Data...\n");
    FILE *fp;
    fp = fopen("persondata.txt", "r");
    if (fp) {
        int id;
        char na[20];
        char sna[20];
        char bdate[11];
        while (fscanf(fp, "%d", &id) != EOF) {
            fscanf(fp, "%s %s %s\n", &na, &sna, &bdate);
            av = newAVL(av, id, na, sna, bdate);
            head->size++;
            person_id++;
        }
        fclose(fp);
    } else {
        printf("ERROR: Cannot read people's data.");
        exit(0);
    }
    // Read Task Data File
    printf("Loading Task Data...\n");
    fp = fopen("taskdata.txt", "r");
    if (fp) {
        int idd;
        char tname[100];
        char ddate[15];
        char dtime[10];
        while (fscanf(fp, "%d %s %s %s", &idd, &tname, &ddate, &dtime) != EOF) {
            addTask(av, idd, tname, ddate, dtime);
        }
        fclose(fp);
    } else {
        printf("ERROR: Cannot read task's data.");
        exit(0);
    }
    // Now It's Running
    char inp;
    while (1 == 1) {
        printf("===== DayList - Staff =====\nChoose an Option:\n");
        printf("P - Show All Persons\nC - Check People\nA - Add People\nT - Add Tasks\nR - Remove Tasks\nS - Exit\n");
        printf("Option > ");
        scanf(" %c", &inp);
        if (inp == 'P') {
            showAllPersons(av);
        } else if (inp == 'A') {
            addPeople(av);
        } else if (inp == 'T') {
            int idd;
            printf("Enter Person ID: ");
            scanf("%d", &idd);
            int status = checkPerson(idd, av, 'R');
            if (status == 1) {
                char tname[100];
                char ddate[15];
                char dtime[10];
                printf("Enter To-Do Name (Use - for Spaces): ");
                scanf("%s", &tname);
                printf("Enter Due Date (YYYY-MM-DD): ");
                scanf("%s", &ddate);
                printf("Enter Date Time (HH:MM 24H): ");
                scanf("%s", &dtime);
                addTask(av, idd, tname, ddate, dtime);
                printf("Task added successfully.\n");
            } else {
                printf("Person with ID %d not found in database.\n", idd);
            }
        } else if (inp == 'R') {
            int idd;
            printf("Enter Person ID: ");
            scanf("%d", &idd);
            int status = checkPerson(idd, av, 'R');
            if (status == 1) {
                char tname[100];
                printf("Enter To-Do Name to be removed (Use - for Spaces): ");
                scanf("%s", &tname);
                status = removeTask(av, idd, tname);
                if (status == 1) {
                    printf("Task removed successfully.\n");
                } else {
                    printf("Task with name %s not found.", tname);
                }
            } else {
                printf("Person with ID %d not found in database.\n", idd);
            }
        } else if (inp == 'C') {
            int idd;
            printf("Enter Person ID: ");
            scanf("%d", &idd);
            int status = checkPerson(idd, av, 'P');
            if (status == 0) {
                printf("Person with ID %d not found in database.\n", idd);
            }
        } else if (inp == 'S') {
            printf("Saving Person Data...\n");
            FILE *fp;
            fp = fopen("persondata.txt", "w");
            savePerson(fp, av);
            fclose(fp);
            printf("Saving Task Data...\n");
            fp = fopen("taskdata.txt", "w");
            saveTask(fp, av);
            fclose(fp);
            break;
        }
    }
    free(head);
    return 0;
}
