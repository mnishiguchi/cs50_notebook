/**
 * hellofunction.c
 * cs50 week2 section
 *
 * Masatoshi Nishiguchi
 *
 * Write a program in which main calls another function that prints out a greeting to the user.
 * It's essentially taking hello world and abstracting that printf into another function
 */
  #include <cs50.h>
  #include <stdio.h>
  
  void hellofunction();
  
  int main(void)
  {
    printf("\nWhat is your name?\n");
    string name = GetString();
    hellofunction(name);
    return 0; 
  }
  
  //function that prints out a greeting to the user
  void hellofunction(string s)
  {
    printf("Hello, %s!!!\n\n", s);
  }
  
  
