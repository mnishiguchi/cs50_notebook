/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 * 
 * resizes 24-bit uncompressed BMPs by a factor of n
 *
 * Usage: ./resize n infile outfile
 * 
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * check 50 passed
 */ 
     
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

// prototype
int getPadding(LONG biWidth);


int main(int argc, char* argv[])
{
    /**
     * check user's input and handle errors if any
     */ 
    
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // ensure proper input of factor
    int factor = atoi(argv[1]);
    if (factor < 1 || factor > 100)
    {
        printf("Factor n must be a positive integer less than or equal to 100\n");
        return 2;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
        return 5;
    }
    
    
      /**
     * update BITMAPFILEHEADER and BITMAPINFOHEADER
     */

    // remember infile's BMP dimention before updating
    int inWidth = bi.biWidth;
    int inHeight = bi.biHeight;

    // determine infile's padding
    int inPadding = getPadding(inWidth);

    // outfile's padding
    int outPadding;

    if (factor == 1)
    {
        outPadding = inPadding;
    }
    else
    {
        // update width of the bitmap, in pixels (not including padding)
        bi.biWidth *= factor;

        // update height of the bitmap, in pixels
        bi.biHeight *= factor;

        // determine outfile's padding
        outPadding =  getPadding(bi.biWidth);

        // Specifies oufile's image size, in bytes (including padding)
        bi.biSizeImage = (3 * bi.biWidth + outPadding) * abs(bi.biHeight);

        // determine outfile's padding
        outPadding =  getPadding(bi.biWidth);

        // update size of the BMP file in bytes
        bf.bfSize = (3 * bi.biWidth + outPadding) * abs(bi.biHeight) + 54;
    }
       
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    
    /**
     * resize BMP image data
     */
    
    // iterate over infile's scanlines
    for (int i = 0; i < abs(inHeight); i++)
    { 
        // temporary storage for all the pixels on current scanline
        RGBTRIPLE tripleArray[inWidth];
        
        for (int j = 0; j < inWidth; j++)
        {
            // temporary storage for pixel
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // remember pixels
            tripleArray[j] = triple;
        }
        
        // expand each scanline * factor times vertically 
        for (int y = 0; y < factor; y++)        
        {
            for (int index = 0; index < inWidth; index++) 
            {
                // expand each pixel * factor times horizontally 
                for (int x = 0; x < factor; x++) 
                {
                    fwrite(&(tripleArray[index]), sizeof(RGBTRIPLE), 1, outptr);
                }   
            }
             
            // add padding to each scanline of outfile
            for (int k = 0; k < outPadding; k++)
            {
                fputc(0x00, outptr);
            }  
        }
        
        // move the infile's pointer to beginning of next scanline
        fseek(inptr, inPadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}


// calculate how many bytes of padding is necessary for biWidth
int getPadding(LONG biWidth)
{
    int padding = (4 - (biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    return padding;
}
