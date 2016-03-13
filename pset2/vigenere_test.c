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
        return 1;
    
    
    int n_key = strlen(argv[1]);
 
    
    // print each letter in keyword
    for (int i = 0; i < n_key; i++)
    {
        printf("argv[1][%d]: %c\n", i, argv[1][i]);
    }
    printf("\n");
    
    // check if keyword is composed entirely of alphabetical characters
    for (int i = 0; i < n_key; i++)
    {
        if (!isalpha(argv[1][i]))
            {
            printf("error\n\n");
            return 1;
            }
        else    // convert all the characters to lower case
        {
            argv[1][i] = tolower(argv[1][i]);
            printf("argv[1][%d]: %c\n", i, argv[1][i]);
        }
    }
    printf("\n");
    
    // prompt the user for a string of plaintext
        string str = GetString();
    
    // rotate each alphabetical character according to key
    int n_str = strlen(str);  
    int idx_str;         // alphabetical index of plaintest
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
            // if it's upper case, convert to lower case
            if (isupper(str[i]))
                {
                upper = 1;
                str[i] = tolower(str[i]);
                }
            
            // calculate alphabetical index
            idx_str =  str[i] - 'a';             //OK
            idx_key = (argv[1][key_pos])- 'a';   //OK
                    
            // calculate alphabetical index of ciphertext   
            idx_cip = (idx_str + idx_key) % 26;
            str[i] = 'a' + idx_cip;
               
            printf("str[%2d]: %c , key_pos: %2d, key(char)[%3d]: %3d, idx_key: %3d\n", 
                    i, str[i], key_pos, key_pos, argv[1][key_pos], idx_key );
            
            // maintain capitalization
            if (upper)
                str[i] = toupper(str[i]);
            
            // update key position
            if (key_pos == (n_key - 1))
                key_pos = 0;
            else
                key_pos++;         
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
