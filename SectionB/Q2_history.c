#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char url[51];
    struct Node *prev;
    struct Node *next;
} Node;

Node *current = NULL;

// Create a new page
Node* createNode(char url[]) {
    Node *temp = (Node*)malloc(sizeof(Node));
    strcpy(temp->url, url);
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}

// Delete all pages after current
void deleteForward(Node *curr) {
    Node *temp = curr->next;
    while (temp != NULL) {
        Node *nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    curr->next = NULL;
}

// VISIT command
void visit(char url[]) {
    if (current == NULL) {
        current = createNode(url);
        return;
    }

    deleteForward(current);

    Node *newNode = createNode(url);
    current->next = newNode;
    newNode->prev = current;
    current = newNode;
}

// BACK command
void back() {
    if (current == NULL || current->prev == NULL)
        printf("NO_BACK\n");
    else {
        current = current->prev;
        printf("%s\n", current->url);
    }
}

// FORWARD command
void forward() {
    if (current == NULL || current->next == NULL)
        printf("NO_FORWARD\n");
    else {
        current = current->next;
        printf("%s\n", current->url);
    }
}

// CURRENT command
void showCurrent() {
    if (current == NULL)
        printf("NONE\n");
    else
        printf("%s\n", current->url);
}

int main() {
    int q;
    scanf("%d", &q);

    while (q--) {
        char command[20];
        scanf("%s", command);

        if (strcmp(command, "VISIT") == 0) {
            char url[51];
            scanf("%s", url);
            visit(url);
        }
        else if (strcmp(command, "BACK") == 0) {
            back();
        }
        else if (strcmp(command, "FORWARD") == 0) {
            forward();
        }
        else if (strcmp(command, "CURRENT") == 0) {
            showCurrent();
        }
    }

    return 0;
}