/**
 * randomName.c
 * cs50 week2 section
 *
 * Masatoshi Nishiguchi
 *
 * This is a program that asks the user for names,
 * then randomly choose and print out one of the names
 */
 
 #include <cs50.h>
 #include <stdio.h>
 #include <time.h>
 #include <stdlib.h>
 #define NUMBER 3   // Number of the people
 
 int main(void)
 {
    // asks the user for names
    string name[NUMBER];
    printf("Please type %d names\n\n", NUMBER);
    
    for (int i = 0; i < NUMBER; i++)
    {
        printf("Name #%d : ", i+1);
        name[i] = GetString();
    }
    
    // randomly choose and print out one of the names
    srand(time(NULL));
    int r = rand() % NUMBER;
    printf("\nThe lucky person is : %s\n\n", name[r]);
 }
 
