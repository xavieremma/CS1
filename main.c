#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// usual directives

typedef struct Customer {
    char name[20];
    int points;
    struct Customer* left;
    struct Customer* right;
} Customer;
// struct representing customer

Customer* createCustomer(const char name[], int points);
void addPoints(Customer** root, const char name[], int points);
void subtractPoints(Customer** root, const char name[], int points);
void deleteCustomer(Customer** root, const char name[]);
Customer* findMax(Customer* node);
void searchCustomer(Customer* root, const char name[], int depth);
int countSmallerNames(Customer* root, const char name[]);
void inOrderTraversal(Customer* root, Customer** sortedArray, int* index);
int compareCustomers(const void* a, const void* b);
// function declarations

int main() {
    int n;
    scanf("%d", &n);

    Customer* root = NULL;

    for (int i = 0; i < n; i++) {
        char command[10];
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            char name[20];
            int points;
            scanf("%s %d", name, &points);
            addPoints(&root, name, points);
        } else if (strcmp(command, "sub") == 0) {
            char name[20];
            int points;
            scanf("%s %d", name, &points);
            subtractPoints(&root, name, points);
        } else if (strcmp(command, "del") == 0) {
            char name[20];
            scanf("%s", name);
            deleteCustomer(&root, name);
        } else if (strcmp(command, "search") == 0) {
            char name[20];
            scanf("%s", name);
            searchCustomer(root, name, 0);
        } else if (strcmp(command, "count_smaller") == 0) {
            char name[20];
            scanf("%s", name);
            int count = countSmallerNames(root, name);
            printf("%d\n", count);
        }
    }
// all commands for add sub delete and search
    
    Customer* sortedArray[n];
    int index = 0;
    inOrderTraversal(root, sortedArray, &index);

    qsort(sortedArray, n, sizeof(Customer*), compareCustomers);

    for (int i = 0; i < n; i++) {
        printf("%s %d\n", sortedArray[i]->name, sortedArray[i]->points);
    }

    return 0;
}
// sorting of names within the index through binary trees


Customer* createCustomer(const char name[], int points) {
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    strcpy(newCustomer->name, name);
    newCustomer->points = points;
    newCustomer->left = newCustomer->right = NULL;
    return newCustomer;
}
// function definitions

void addPoints(Customer** root, const char name[], int points) {
    
    if (*root == NULL) {
        *root = createCustomer(name, points);
        printf("%s %d\n", name, points);
    } else if (strcmp(name, (*root)->name) < 0) {
        addPoints(&(*root)->left, name, points);
    } else if (strcmp(name, (*root)->name) > 0) {
        addPoints(&(*root)->right, name, points);
    } else {
        (*root)->points += points;
        printf("%s %d\n", name, (*root)->points);
    }
}
// implementing add point functions

void subPoints(Customer** root, const char name[], int points) {
    
    if (*root == NULL) {
        printf("%s 0\n", name);
    } else if (strcmp(name, (*root)->name) < 0) {
        subPoints(&(*root)->left, name, points);
    } else if (strcmp(name, (*root)->name) > 0) {
        subPoints(&(*root)->right, name, points);
    } else {
        if (points >= (*root)->points) {
            (*root)->points = 0;
        } else {
            (*root)->points -= points;
        }
        printf("%s %d\n", name, (*root)->points);
    }
}
// implementing of sub functions

void delCustomer(Customer** root, const char name[]) {
    
    if (*root == NULL) {
        printf("not found\n");
    } else if (strcmp(name, (*root)->name) < 0) {
        delCustomer(&(*root)->left, name);
    } else if (strcmp(name, (*root)->name) > 0) {
        delCustomer(&(*root)->right, name);
    } else {
        if ((*root)->left == NULL) {
            Customer* temp = (*root)->right;
            free(*root);
            *root = temp;
        } else if ((*root)->right == NULL) {
            Customer* temp = (*root)->left;
            free(*root);
            *root = temp;
        } else {
            Customer* temp = findMax((*root)->left);
            strcpy((*root)->name, temp->name);
            (*root)->points = temp->points;
            delCustomer(&(*root)->left, temp->name);
        }
        printf("%s deleted\n", name);
    }
}
// implementation of delete customer function

Customer* findMax(Customer* node) {
    
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

void searchCustomer(Customer* root, const char name[], int depth) {
    
    if (root == NULL) {
        printf("not found\n");
    } else if (strcmp(name, root->name) < 0) {
        searchCustomer(root->left, name, depth + 1);
    } else if (strcmp(name, root->name) > 0) {
        searchCustomer(root->right, name, depth + 1);
    } else {
        printf("%s %d %d\n", name, root->points, depth);
    }
}
// implementing of search customer function


int countSmallNames(Customer* root, const char name[]) {
   
    if (root == NULL) {
        return 0;
    }
    if (strcmp(name, root->name) <= 0) {
        return countSmallNames(root->left, name);
    }
    return 1 + countSmallNames(root->left, name) + countSmallNames(root->right, name);
}

void inOrderTraversal(Customer* root, Customer** sortedArray, int* index) {
    if (root != NULL) {
        inOrderTraversal(root->right, sortedArray, index);
        sortedArray[*index] = root;
        (*index)++;
        inOrderTraversal(root->left, sortedArray, index);
    }
}
// implementing traversal function

int compareCustomers(const void* a, const void* b) {
    
    Customer* customerA = *(Customer**)a;
    Customer* customerB = *(Customer**)b;

    if (customerA->points != customerB->points) {
        return customerB->points - customerA->points;
    }

    return strcmp(customerA->name, customerB->name);
}
// implementation of compare customers function
