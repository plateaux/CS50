#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //check number of arguments
    if (argc != 2)
    {
    printf("Error. Please use one word as an argument.\n");
    return 1;
    }
    
    string keyWord = argv[1];
    int keyWordLength = strlen(keyWord);
    
    //check if each char in keyword is a letter
    for (int x = 0; x < keyWordLength; x++)
    {
        //debug: printf("Checking if %c is alpha.\n", keyWord[x]);
        if(isalpha(keyWord[x]) == 0)
        {
            printf("Error. Please use only letters in keyword.\n");
            return 1;
        }
    } //end of for loop checking for valid alpha keyword
    
    string plainText = GetString();
    int textLength = strlen(plainText);
    char encryptedLetter;
    
    for(int i = 0, k = 0; i < textLength; i++)
    {
        
        //check if alphanumeric letter
        if (isalpha(plainText[i])) 
        {
            //check for upper case letters
            if (plainText[i] >= 'A' && plainText[i] <= 'Z')
            {
                //set the key
                int key = keyWord[k % keyWordLength]-65; //key algorithm
                k += 1; //increment key only on alphas
                encryptedLetter = ((plainText[i]-65)+key) % 26 + 'A';
            } // end of if
            else
            {
                //check for lower case letter
                if (plainText[i] >= 'a' && plainText[i] <= 'z')
                {
                    int key = keyWord[k % keyWordLength]-97; //key algorithm
                    k += 1; //increment key only on alphas
                    encryptedLetter = ((plainText[i]-97)+key) % 26 + 'a';
                }
            } //end of else  
        } //end of if checking isalpha()
        
        else //for non-alphanumeric chars, pass existing letter
        {
            encryptedLetter = plainText[i];
        }
        
        printf("%c", encryptedLetter);
    }// end of for loop
    
    printf("\n"); //print newline character after end of for loop
    
} //close main
