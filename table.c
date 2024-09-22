#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    char* key;
    char* value;

    struct node* next;
} Node;

typedef struct table {
    Node* first;
    Node* last;

    int size;
} Table;

Node* create_node(char* key, char* value) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;

    newNode->next = NULL;

    return newNode;
}

Table* initialize_table() {
    Table* newTable = (Table*) malloc(sizeof(Table));
    newTable->first = NULL;
    newTable->last = NULL;
    
    newTable-> size = 0;

    return newTable;
}

void insert_to_table(char* key, char* value, Table* table) {
    Node* newNode = create_node(key, value);

    if (table->size == 0) {
        table->first = newNode;
    } else {
        table->last->next = newNode;
    }

    table->last = newNode;
    ++table->size;
}

bool key_exists(char* key, Table* table) {
    Node* currentNode = table->first;
    while (currentNode != NULL) {
        if (strcmp(key, currentNode->key) == 0) {
            return true;
        }
        currentNode = currentNode->next;
    }

    return false;
}

char* get_value(char* key, Table* table) {
    Node* currentNode = table->first;
    while (currentNode != NULL) {
        if (strcmp(key, currentNode->key) == 0) {
            return currentNode->value;
        }
        currentNode = currentNode->next;
    }

    return "";
}

void print_table(Table* table) {
    if (table->size == 0) {
        printf("\nTable is empty\n");
        return;
    }

    Node* currentNode = table->first;
    printf("\n");
    while (currentNode != NULL) {
        printf("\t%s - %s\n", currentNode->key, currentNode->value);
        currentNode = currentNode->next;
    }
}