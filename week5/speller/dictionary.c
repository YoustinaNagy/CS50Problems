// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 20000;

// counter
int counter;

// Hash table
node *table[N];

// Hashes word to a number
unsigned int hash(const char *word)
{
    int value = 0;
    int i = 0;
    for(i = 0; i < strlen(word); i++) {
        value += tolower(word[i]) % N;
    }
    return value;
}

bool check(const char *word)
{
    int hashValue = hash(word);
    for(node * temp = table[hashValue]; temp != NULL; temp = temp->next ){
        if(strcasecmp(temp->word, word) == 0){
            return true;
        }
    }
    return false;
}

bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist!!");
        return false;
    }
    char temp[100];
    counter = 0;
    while (fscanf(file, "%s", temp) != EOF) {
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL) {
            return false;
        }
        counter += 1;
        newNode->next = NULL;
        strcpy(newNode->word, temp);
        int hashValue = hash(temp);
        if (table[hashValue] == NULL) {
            table[hashValue] = newNode;
        } else {
            newNode->next = table[hashValue];
            table[hashValue] = newNode;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // simply return counter
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *it = table[i];
        while (it != NULL)
        {
           node *tmp = it;
           it = it->next;
           free(tmp);
        }
    }
    return true;
}
