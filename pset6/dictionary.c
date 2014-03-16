/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// global trie struct for letters
// Kudos to this tutorial for examples: http://simplestcodings.blogspot.com/2012/11/trie-implementation-in-c.html
typedef struct trie
{
    bool isAWord;
    struct trie* children[27];
} 
trie;

trie* firstNode;

// number of words loaded
int numberOfWords = 0;

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    int aAsInt = (int)'a';
    int zAsInt = (int)'z';
    
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        return false;
    }

    // malloc memory for firstNade
    firstNode = malloc(sizeof(trie));
    int character = 0;
    
    // use trie* currentNode as cursor
    trie* currentNode = NULL;

	//loop through dictionary until end of file EOF
    while(fgetc(fp) != EOF)
    {
        fseek(fp, -1, SEEK_CUR);

        // set cursor to firstNode
        currentNode = firstNode;

		//loop through characters until \n
        for (character = fgetc(fp); character != '\n'; 
                character = fgetc(fp))
        {    
            // if apostrophes, set character to z+1
            if (character == '\'')
            {
                character = zAsInt + 1;
            }

            // If the character is not in trie...
            if (currentNode->children[character - aAsInt] == NULL)
            {
                // ... malloc a new node and go there
                currentNode->children[character - aAsInt] = malloc(sizeof(trie));
                currentNode = currentNode->children[character - aAsInt];
	        }
	        else // ... but if it is, go to the existing node
            {
                currentNode = currentNode->children[character - aAsInt];
	        }
	    }

        currentNode->isAWord = true;
        numberOfWords++;
    }
    fclose(fp);
    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int aAsInt = (int)'a';
    int zAsInt = (int)'z';
    // set a trie* to point to firstNode
    trie* currentNode = firstNode;
	
	//loop through word
	int i = 0;
	while(word[i] != '\0')
    {
        char inChar = word[i];
        
        // find apostrophes
        if (word[i] == '\'')
        {
            inChar = zAsInt + 1;
        }
		
        int childIndex = tolower(inChar) - aAsInt; 	//index to check for child node
       
        // go to childIndex if not NULL, else return false
        if (currentNode->children[childIndex] != NULL)
        {
            currentNode = currentNode->children[childIndex];
            i++;
	    }  
        else
        {
            return false;
         } 
    } // close for loop
    
    // if word exists, return true.
    if (currentNode->isAWord == true)
    {
        return true;
    }
	else
	{
    return false;
	}
}

/**
 * Returns number of words in dictionary if loaded.
 */
unsigned int size(void)
{
    return numberOfWords;
}

/**
 * Unloads dictionary from memory
*/
bool unload(void)
{
	// free each of the children if not NULL
    for(int unloadI = 0; unloadI < 27; unloadI++)
    {
		trie* currentNode = firstNode;
        if (currentNode->children[unloadI] != NULL)
        {
            free(currentNode->children[unloadI]);  
        }      
	}
    return true;
}
