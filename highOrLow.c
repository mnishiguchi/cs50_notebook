#include <cs50.h>
#include <stdio.h>

int main(void){
    printf("Give me an integer:  ");
    int n = GetInt();
    
    string s = (n > 100)? "high":"low";
    
    printf("%d: You picked a %s number!!!\n", n, s);
}
