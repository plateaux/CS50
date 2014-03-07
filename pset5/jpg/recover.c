/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 //#include "bmp.h" - check50 doesn't work with this

typedef uint8_t  BYTE; //from bmp.h


int main(int argc, char* argv[])
{
    //open raw file
    FILE* rawFile = fopen("card.raw", "r");
    
    if (rawFile == NULL)
    {
        printf("Could not open \"card.raw\".");
        return 2;
    }
    
    BYTE* buffer = malloc(512);
    int fileNumber = 0;
    FILE* outFile = NULL;

    while(fread(buffer, 512, 1, rawFile))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (buffer[3] == 0xe0 || buffer[3] == 0xe1)
            {
                // make sure outFile is still NULL
                if (outFile != NULL)
                {
                    fclose(outFile);
                }
                
                char fileName[8]; // enough chars for filename + \0
                sprintf(fileName, "%03d.jpg", fileNumber);
                outFile = fopen(fileName, "w");
                fileNumber++;
         
            } // close if 4th byte JPEG check
        } // close main if JPEG check
        
        
        //if JPEG found and outFile was opened, write data to file
        if (outFile != NULL)
        {
            fwrite(buffer, 512, 1, outFile);
        }
        
        // free(buffer);
    } // close while loop interating over file

    fclose(rawFile);
    return 0;
 }
