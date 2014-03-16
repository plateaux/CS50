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

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
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
				int zAsInt = (int)'z';
                character = zAsInt + 1;
            }

            // If the character is not in trie...
            if (currentNode->children[character - 'a'] == NULL)
            {
                // ... malloc a new node and go there
                currentNode->children[character - 'a'] = malloc(sizeof(trie));
                currentNode = currentNode->children[character - 'a'];
	        }
	        else // ... but if it is, go to the existing node
            {
                currentNode = currentNode->children[character - 'a'];
	        }
	    }

        currentNode->isAWord = true;
        numberOfWords++;
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded.
 */
unsigned int size(void)
{
    return 0;
}


/**
 * Unloads dictionary from memory
*/
bool unload(void)
{
    return false;
}
