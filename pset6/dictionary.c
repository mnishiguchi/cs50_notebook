/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * check50 passed, memory leak checked with Valgrind
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "dictionary.h"

// create hash table
node* hashtable[TABLE_SIZE];    /* array of node-type pointers */

// dictionary's size
int dictionary_size = 0;

/********************************************************************
 * Check if word is in dictionary
 * Returns true if word is in dictionary; else false.
 ********************************************************************/
bool check(const char* word)
{
    // copy word to temp
    char temp[LENGTH + 1];   /* max length + '\0' terminator */
    strcpy(temp, word);
    
    // convert to lower case
    for (int i = 0; word[i] != '\0'; i++)
    {
        temp[i] = (char)tolower(temp[i]);
    }
    
    // get hash index for word
    int hash_index = hash_function(word);
    
    // node pointer, pointing first node 
    node* cursor = hashtable[hash_index];
           
    // iterate over the linked list until the end
    while (cursor != NULL)
    {
        // if found
        if (strcmp(temp, cursor->word) == 0)
        {
            return true;
        }
        // if not found yet
        else
        {
            // move cursor to next node, and continue
            cursor = cursor->next;  
        }
    }

    // if not found in lined list, this word is not in dictionary
    return false;
}

/********************************************************************
 * Loads dictionary into memory.  
 * Returns true if successful; else false.
 ********************************************************************/
bool load(const char* dictionary)
{        
  /*===================
      open dictionary    
    ===================*/ 
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Invalid file specified.\n");
        return false;
    }
             
  /*======================================
      Read all the words from dictionary  
    ======================================*/
    while (true)
    {
        // create and malloc new node for each word
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("not enough memory to load\n");
            return false;
        }
 
        // read word from dictionary to new node
        if (fscanf(fp, "%s", new_node->word) == EOF)
        {
             // if EOF is reached, free unused memory and exit loop
             free(new_node);
             break;
        }
        
        // update dictionary size
        dictionary_size++;
        
      /*=================
          Hash Function  
        =================*/
        int hash_index = hash_function(new_node->word);
    
        if (TABLE_SIZE < hash_index)
        {
            printf("Hash function error.\n");
            return false;
        }
        
      /*==========================================
          Insert node(word) into the linked list  
        ==========================================*/
        // if no node exists in linked list
        if (hashtable[hash_index] == NULL)
        {
            hashtable[hash_index] = new_node;
            new_node->next = NULL;
        }
        else
        {
            // insertion at the beginning of the linked list
            new_node->next = hashtable[hash_index];
            hashtable[hash_index] = new_node;
        }
    }
    
    // close dictionary
    fclose(fp);
 
    return true;
}

/********************************************************************
 * Returns number of words in dictionary if loaded; 
 * else 0 if not yet loaded.
 ********************************************************************/
unsigned int size(void)
{
    return dictionary_size;
}

/********************************************************************
 * Unloads dictionary from memory. 
 * Free every node in the hashtable. 
 * Returns true if successful; else false.
 ********************************************************************/
bool unload(void)
{ 
    for (int i = 0; i < TABLE_SIZE ; i++)
    {
        // pointing to head of linked list
        node* cursor = hashtable[i];
        
        while (cursor != NULL)
        {
            // temp pointer for current
            node* current = cursor;
            
            // move cursor to next node
            cursor = cursor->next;
            
            // free current node
            free(current);    
        }
    }
    return true;
}

/********************************************************************
 * Calculate hash index for each word passed
 * Returns hash index
 ********************************************************************/    
int hash_function(const char* word)
{       
    // initialize ascii sum and hash index
    unsigned int ascii = 0;   
    unsigned int hash_index = 32767;
 
   // sum all ascii values of word
    for (int i = 0; word[i] != '\0'; i++)
    { 
        // convert all characters into lowercase for consistency
        ascii += (int)tolower(word[i]);
    }
       
    // hash formula : mod by table size
    hash_index = ascii % TABLE_SIZE;  
                        
    return hash_index;
}
