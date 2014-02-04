#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char * argv[])
{
    //check number of arguments and if positive
    if (argc != 2 || argv[1] <= 0)
    {
    printf("Error. Please use one positive number as an argument.\n");
    return 1;
    }

    int key = atoi(argv[1]);
    string plainText = GetString();
    int textLength = strlen(plainText);
    char encryptedLetter;
    
    for(int i = 0; i < textLength; i++)
    {
        //check if it's a alphanumeric letter
        if (isalpha(plainText[i])) 
        {
            //check for upper case letters
            if (plainText[i] >= 'A' && plainText[i] <= 'Z')
            {
                encryptedLetter = ((plainText[i]-'A')+key) % 26 + 'A';

            } // end of if
            else
            {
                //check for lower case letter
                if (plainText[i] >= 'a' && plainText[i] <= 'z')
                {
                    encryptedLetter = ((plainText[i]-'a')+key) % 26 + 'a';
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
