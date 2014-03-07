/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // remember filenames
    int resizeFactor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    //create new headers for outfile
    BITMAPFILEHEADER bfOut;
    BITMAPINFOHEADER biOut;
    bfOut = bf;     //copy infiles file header
    biOut = bi;     //copy infiles info header
    biOut.biWidth = bi.biWidth * resizeFactor;      //resize outfiles width by resizeFactor
    biOut.biHeight = bi.biHeight * resizeFactor;    //resize outfiles height by resizeFactor
    int paddingIn =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;    //set padding for infile
	int paddingOut =  (4 - (biOut.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;    //set padding for outfile
	bfOut.bfSize = 54 + biOut.biWidth * abs(biOut.biHeight) * 3 + abs(biOut.biHeight) *  paddingOut;    //change outfile file size
	biOut.biSizeImage = ((((biOut.biWidth * biOut.biBitCount) + 31) & ~31) / 8) * abs(biOut.biHeight);      //change outfile biSizeImage
	

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfOut, sizeof(BITMAPFILEHEADER), 1, outptr);
   
    // write outfile's BITMAPINFOHEADER
    fwrite(&biOut, sizeof(BITMAPINFOHEADER), 1, outptr);

    //get number of lines in infile
    int biHeight = abs(bi.biHeight);
    
    // iterate over infile's scanlines
    for (int i = 0; i < biHeight; i++)
    {
    
        //Copy scanline * resizeFactor
        for (int m = 0; m < resizeFactor; m++)
        {   
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // copy pixel n number of times
                for(int l = 0; l < resizeFactor; l++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, paddingIn, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < paddingOut; k++)
            {
                fputc(0x00, outptr);
            }
            
            /* set file position indicator back to beginning of line
               and step through the line*resizeFactor for loop again
               to copy the same line resizeFactor number of time
            */
            fseek(inptr, - (bi.biWidth * 3 + paddingIn ), SEEK_CUR);
            
        }//end line*resizeFactor for loop
        
        /* Once out of the line*resizeFactor loop,
           set the file position indicator to new line
        */
        fseek(inptr, bi.biWidth * 3 + paddingIn, SEEK_CUR);
        
    }//end main for loop
   

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
