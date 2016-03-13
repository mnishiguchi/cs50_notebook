/**
 * vigenere.c
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * check50: passed
 *
 * encipher a user-input plaintext
 *
 * usage: ./vigenere <keyword>
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
        printf("usage: ./vigenere <keyword>\n");
        return 1;
    }
        
    // check if keyword is composed entirely of alphabetical characters
    int key_len = strlen(argv[1]);
    
    for (int i = 0; i < key_len; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Only alphabetical characters are accepted\n");
            return 1;
        }
        // convert all the characters in keyword to lower case
        else    
        {
            argv[1][i] = tolower(argv[1][i]);
        }
    }
    
    // prompt the user for a plaintext
        string str = GetString();
    
    // rotate each alphabetical character according to keyword
    int str_len = strlen(str);  
    int idx_str;         // alphabetical index of plaintext
    int idx_cip;         // alphabetical index of ciphertext
    int idx_key;         // alphabetical index of keyword
    int upper;           // 1: upper case, 0: lower case 
    int key_pos = 0;     // remember which character of keyword in use

    for (int i = 0; i < str_len; i++)
    {
        idx_str = 0;
        idx_cip = 0;
        idx_key = 0;
        upper = 0;
         
        if (isalpha(str[i]))
        {
            // examine each user input characters and
            // if it's upper case, convert to lower case
            if (isupper(str[i]))
            {
                upper = 1;
                str[i] = tolower(str[i]);
            }
            
            // calculate alphabetical index
            idx_key = (argv[1][key_pos]) - 'a';   // for keyword
            idx_str =  str[i] - 'a';              // for plaintext      
            idx_cip = (idx_str + idx_key) % 26;   // for ciphertext
            
            // assign each encrypted character to str[i]
            str[i] = 'a' + idx_cip;
               
            // maintain capitalization
            if (upper)
            {
                str[i] = toupper(str[i]);
            }
            
            // update keyword position
            if (key_pos == (key_len - 1))
            {
                key_pos = 0;    // go back to first character
            }
            else
                key_pos++;      // move to next character
        }
    }
     
    // print ciphertext
    for (int i = 0; i < str_len; i++)
    {
        printf("%c", str[i]); 
    }
    printf("\n");
     
    return 0; 
}
