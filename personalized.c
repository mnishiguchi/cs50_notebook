/**
 * personalized.c
 * cs50 week2 section
 *
 * takes a user's full name (two and only two command line arguments) 
 * print out a greeting to the user that includes their first name.
 *
 * usage: ./personalized <first name> <last name> // as a command line prompt
 */
 
 #include <cs50.h>
 #include <stdio.h>
 #include <string.h>
 
 int main (int argc, string argv[])
 {
     //takes a user's full name (two and only two command line arguments) 
     if (argc != 3) 
         return 1;   
     
     printf("argc = %d\n", argc);
     for (int i = 0; i < 10; i++)
     {
        printf("argv[%d] = %s\n", i, argv[i]); 
     }
           
     //print out a greeting to the user that includes their first name.
     printf("\nHello %s!!!!\n", argv[1]);
 }
