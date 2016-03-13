/**
 * vigenere.c
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * encipher a user-input plaintext
 *
 * usage:
 *     when run, type an alphabatical keyword following the program name.
 *     example: ./vigenere <keyword>
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // check if excuted with a single command-line argument
    if (argc != 2)
        {
        printf("error\nPlease start again.\n\n");
        return 1;
        }
        
    // check if keyword is composed entirely of alphabetical characters
    int n_key = strlen(argv[1]);
    
    for (int i = 0; i < n_key; i++)
    {
        if (!isalpha(argv[1][i]))
            {
            printf("error\nPlease start again.\n\n");
            return 1;
            }
        else    // convert all the characters in keyword to lower case
        {
            argv[1][i] = tolower(argv[1][i]);
        }
    }
    
    // prompt the user for a string of plaintext
        string str = GetString();
    
    // rotate each alphabetical character according to keyword
    int n_str = strlen(str);  
    int idx_str;         // alphabetical index of plaintext
    int idx_cip;         // alphabetical index of ciphertext
    int idx_key;         // alphabetical index of keyword
    int key_pos = 0;     // show which key is in use
    int upper;           // 1: upper case, 0: lower case

    for (int i = 0; i < n_str; i++)
    {
        idx_str = 0;
        idx_cip = 0;
        idx_key = 0;
        upper = 0;
         
        if (isalpha(str[i]))
        {
            // examine each user input characters
            // if it's upper case, convert to lower case
            if (isupper(str[i]))
                {
                upper = 1;
                str[i] = tolower(str[i]);
                }
            
            // calculate alphabetical index
            idx_key = (argv[1][key_pos])- 'a';    // keyword
            idx_str =  str[i] - 'a';              // plaintext      
            idx_cip = (idx_str + idx_key) % 26;   // ciphertext
            
            // assingn encrypted char to str[i]
            str[i] = 'a' + idx_cip;
               
            // maintain capitalization
            if (upper)
                str[i] = toupper(str[i]);
            
            // update key position
            key_pos = (key_pos == (n_key - 1))? 0 : (key_pos+1);
        }
    }
     
    // print ciphertext
    for (int i = 0; i < n_str; i++)
    {
        printf("%c", str[i]); 
    }
    printf("\n\n");
     
    return 0; 
}
