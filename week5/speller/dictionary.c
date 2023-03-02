// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char *word;
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N] = {NULL};


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    int length = strlen(word);
    node *current_node = table[index];
    char given_word[length + 1];
    char *dictionary_word;

    for (int i = 0; i < length + 1; i++)
    {
        given_word[i] = tolower(word[i]);
    }

    while (current_node != NULL) // Checking whether the given word is in dictionary using iteration
    {
        dictionary_word = current_node->word;

        if (strcmp(given_word, dictionary_word) == 0)
        {
            return true;
        }
        else
        {
            current_node = current_node->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Add a character to the word
char *load_character(char c, int i, char *buffer, char *word)
{
    if (c == '\n')
    {
        word = malloc(i + 1);

        for (int j = 0; j < i + 1; j++)
        {
            if (j != i)
            {
                word[j] = buffer[j];
            }
            else
            {
                word[j] = '\0';
            }
        }

        return word;
    }

    buffer[i] = c;
    return NULL;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    char c = 0;
    char buffer[LENGTH];
    char *word = NULL;

    int i = 0;
    while (fread(&c, 1, 1, file))
    {
        if (c == EOF)
        {
            break;
        }

        word = load_character(c, i, buffer, word);

        if (word == NULL)
        {
            i++;
        }
        else
        {
            unsigned int index = hash(word);
            node *new = malloc(sizeof(node));
            new->word = word;
            new->next = table[index];
            table[index] = new;
            i = 0;
        }
    }

    fclose(file);
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int counter = 0;
    node *ptr = NULL;

    for (int i = 0; i < N; i++)
    {
        ptr = table[i];

        while (ptr != NULL) // Using iteration to count the number of words loaded to memory from dictionary
        {
            ptr = ptr->next;
            counter++;
        }
    }

    return counter;
}


// Frees one given list
void free_list(node *ptr)
{
    if (ptr->next != NULL)
    {
        free_list(ptr->next); // Using recursion to free each node one by one
    }
    free(ptr->word);
    free(ptr);
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *ptr = NULL;

    for (int i = 0; i < N; i++)
    {
        ptr = table[i];

        if (ptr != NULL)
        {
            free_list(ptr); // Calling the function free_list which unload a list at a time
        }
    }

    return true;
}