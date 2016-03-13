/**
 * cs50 pset1: greedy
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * ask the user how much change is owed and
 * calculate the total number of coins for change
 */

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{	  
// asking the user how much change is owed
    
    printf("\nHello, cs50!!!\n");
    
    double balance;
    
    do
    {
        printf("How much change do I owe you?\n");
        printf("(Example: If you are owed $9.75, please type 9.75)\n");
        balance = GetDouble();   
    }
    while (balance <= 0);
    
    printf("$%.2lf\n", balance);

    //printf("-------------------------------\n");
     
         
    // converting dollars into cents
    balance *= 100;
    int remainder = round(balance);
    
    // calculate the number of 25 cent coins
    int num_quarters = 0;
    
    if (remainder >= 25)
    {
        num_quarters = remainder / 25;
    }
    remainder -= (num_quarters * 25);
    printf("quarters:     %6d\n", num_quarters);
    
    // calculate the number of 10 cent coins 
    int num_dimes = 0;
    
    if (remainder >= 10)
    {
        num_dimes = remainder / 10;
    }
    remainder -= (num_dimes * 10);
    printf("dimes:        %6d\n", num_dimes);
    
    // calculate the number of 5 cent coins 
    int num_nickels = 0;
    
    if (remainder >= 5)
    {
        num_nickels = remainder / 5;
    }
    remainder -= (num_nickels * 5);
    printf("nickels:      %6d\n", num_nickels);
       
    // calculate the number of 1 cent coins 
    int num_pennies = 0;
    
    if (remainder >= 1)
    {
        num_pennies = remainder;
    }
    remainder -= num_pennies;
    printf("pennies:      %6d\n", num_pennies);

    // total number of coins for change
    int coins;
    coins = num_quarters + num_dimes + num_nickels + num_pennies;
    printf("-------------------------------\n");      
    printf("total:          %6d coins\n", coins);  
         
	printf("\nHave a good day!!!\n\n"); 
	return 0;
}
