/**
 * caesar.c
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * check50: passed
 *
 * encipher a user-input plaintext
 *
 * usage:
 *     when run, type a key(non-negative integer) following the program name.
 *     example: ./caesar 2
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
 
int main(int argc, string argv[])
{
    // check if the program is excuted with one command-line argument
    if (argc != 2)
    {
        printf("usage: ./caesar <key>\n");
        return 1;
    }    
 
    // prompt the user for a string of plaintext
    string s = GetString();
     
    // convert user input key to int
    int key = atoi(argv[1]);   
       
       
    // rotate each alphabetical character according to key
    int n = strlen(s);  
    int index;         // alphabetical index
    int pos;           // distance away from 'a'
    int upper;         // 1: upper case, 0: lower case
     
    for (int i = 0; i < n; i++)
    {
        index = 0; 
        upper = 0;
        pos = 0;
         
        if (isalpha(s[i]))
        {
            // if it's upper case, convert to lower case
            if (isupper(s[i]))
                {
                upper = 1;
                s[i] = tolower(s[i]);
                }
             
            // convert Ascii value to alphabetical index
            index =  s[i] - 'a';
               
            // calculate the distance away from 'a'    
            pos = (index + key) % 26;
            s[i] = 'a' + pos;
             
            // maintain capitalization
            if (upper)
                s[i] = toupper(s[i]);
        }
    }
     
    // print ciphertext
    for (int i = 0; i < n; i++)
    {
        printf("%c", s[i]); 
    }
    printf("\n");
     
    return 0; 
}
