/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * check 50 passed
 */ 

#include <stdio.h>

int main(int argc, char* argv[])
{
    // check user's input
    if (argc != 1)
    {
        printf("Does not accept command line argument\n");
        return 1;
    }
    
    // open memory card file
    FILE* infile = fopen("card.raw", "r");
    if (infile == NULL)
    {
        printf("Invalid file specified.\n");
        return 2;
    }
   
   
    /**
     * find beginning of first jpg
     */
     
    // temporary storage
    unsigned char buffer[512];
    
    // file counter
    int fileCtr = 0;
     
    // find the starting point of first jpeg
    while (1)
    {
        // hover over the infile and read by 512 bytes
        fread(buffer, sizeof(char), 512, infile);
         
        // check if jpg signature exists
        if ( (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) &&
             (buffer[3] == 0xe0 || buffer[3] == 0xe1) )
        {
            break;
        }
        else if (feof(infile) == 1)
        {
            printf("No jpeg data identified\n");
            return 4;
        }
    } 
    
    
    /**
     * create a jpg file for each image data
     */

    while (feof(infile) == 0)
    {
        // create a new jpg file
        char filename[8];
        sprintf(filename, "%03d.jpg", fileCtr);
        FILE* outfile = fopen(filename, "a");

        if (outfile == NULL)
        {
             printf("Could not open a file\n");
             return 5;
        }
        
        while (feof(infile) == 0)
        {
            // write a 512-byte block to outfile
            fwrite(buffer, sizeof(char), 512, outfile); 
            
            // ensure reading 512 bytes
            if (fread(buffer, sizeof(char), 512, infile) != 512)
            {
                break;
            }
            
            // check if jpg signature exists
            if ( (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) &&
                 (buffer[3] == 0xe0 || buffer[3] == 0xe1) )
            {
                // close a current jpg file
                fclose(outfile);
                                        
                // update file counter
              	fileCtr++; 
               	break;
            } 
        }
    }
    
    // exit if there is no jpeg identified 
    if (fileCtr == 0)
    {
        printf("No jpeg data identified\n");
        return 6;
    }
    
    // close infile
    fclose(infile);

    return 0;
}
