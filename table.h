#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>

// Structures
typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

typedef struct Table {
    Node* first;
    Node* last;
    int size;
} Table;

// Function prototypes
/**
 * Creates a new node with the given key and value.
 * 
 * @param key The key of the node.
 * @param value The value associated with the key.
 * @return A pointer to the newly created node.
 */
Node* create_node(char* key, char* value);

/**
 * Initializes a new, empty table.
 * 
 * @return A pointer to the newly created table.
 */
Table* initialize_table();

/**
 * Inserts a key-value pair into the table.
 * 
 * @param key The key to insert.
 * @param value The value associated with the key.
 * @param table The table where the key-value pair will be inserted.
 */
void insert_to_table(char* key, char* value, Table* table);

/**
 * Checks whether a given key exists in the table.
 * 
 * @param key The key to search for.
 * @param table The table to search within.
 * @return true if the key exists, false otherwise.
 */
bool key_exists(char* key, Table* table);

/**
 * Retrieves the value associated with the given key in the table.
 * 
 * @param key The key whose associated value is being retrieved.
 * @param table The table to search within.
 * @return The value associated with the key, or an empty string if the key is not found.
 */
char* get_value(char* key, Table* table);

/**
 * Prints the contents of the table to the console.
 * 
 * @param table The table whose contents will be printed.
 */
void print_table(Table* table);

/**
 * Frees the memory used by the table and its nodes.
 * 
 * @param table The table to be freed.
 */
void free_table(Table* table);

#endif