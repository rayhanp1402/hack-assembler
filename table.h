#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>

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


Node* create_node(char* key, char* value);

Table* initialize_table();

void insert_to_table(char* key, char* value, Table* table);

bool key_exists(char* key, Table* table);

char* get_value(char* key, Table* table);

void print_table(Table* table);

void free_table(Table* table);

#endif