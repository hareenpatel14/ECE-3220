//
//  main.c
//  Lab2
//
//  Created by Hareen Patel on 1/29/17.
//  Copyright © 2017 Hareen Patel. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
void setbuf(FILE *stream, char *buffer);
void mainpath(char option); // creating different functions prototypes to carry out different task
void binary();
int main(int argc, const char * argv[]) {
    setbuf(stdin, NULL);
    char option;
    int option1;
    printf("Choose a function!\nA)Factorial\nB)Leap year checker\nC)Maximun\nD)Division\nE)Exit\n"); // menu print
    scanf( " %c",&option);
    fflush(stdout);
    
    while (option != 'E')
    {
        
        mainpath(option); // calling the main part of the lab
        option = ' ';
        printf("Choose a function!\nA)Factorial\nB)Leap year checker\nC)Maximun\nD)Division\nE)Exit\n"); // menu print
        scanf(" %c",&option);
        fflush(stdout);
        
    }
    
    printf("You have chosen to exit the program!\nHave a greatday!\n");
    
    printf("Press 1 to continue to binary converter, 0 to exit\n"); // menu print for next program
    scanf("%d",&option1);
    if (option1 == 1)
    {
        binary(); // calling binary function
    }
    return 0;
}

void binary()
{
    unsigned short number, placeholder;
    int option;
    
    printf("Enter a number you would like to convert.\n");
        scanf("%hu",&number);
    printf("how would you like to convert? Arithmetic(1) or bitwise(2)\n");
        scanf("%d",&option);
    
    placeholder = number;
    int i, j=31,y=0;
    int buffer[15];
    
    switch (option)
    {
        case 1:
        {
            while(number > 0)
            {
                buffer[y] = number % 2; // getting values of 1 or 0
                y++; // bumping to next location
                number = number/2; // dividing number to get new number
            }
            printf("The Binary representation of %d is: ",placeholder);
            for (i=y-1; i>=0; i--)
            {
                printf("%d",buffer[i]); // going thru each location and printing value
            }
            printf("\n");
            break;
        }
        
        case 2:
        {
            for (j=15; j>=0; j--)
            {
                i = number >> j;
                
                if (i & 1) // checking if the result of 1 & 1 is 1.
                {
                    printf("1");
                }
                else
                {
                    printf("0");
                }
            }
            printf("\n");
            break;
        }
    }
}

void mainpath(char option)
{
 
  
    switch (option)
    {
        
        case 'A':
        {
        unsigned short input;
        unsigned long output = 1;
        
        int i=1;
        printf("You want to calculate a facotrial\n");
        printf("Please select a number between 0 and 12\n");
            scanf("%hu",&input);
                while (input<0||input>12) // while loop to make sure number is valid
                {
                    printf("You have selelcted the wrong number, enter new number: ");
                    scanf("%hu",&input);
                }
            for(i=1;i<=input;i++)
                {
                    output *= i; // factorial. bumps i however many times user said.
                }
            printf("the factorial for %hu is %lu!\n\n",input,output); // prints factorial
            break;
            
        }
       case 'B':
        {
            unsigned int year;
            printf("You want to know if it's a leap year!\n");
            printf("Please enter a year that you would like to check\n");
                scanf("%u",&year);
            if (year%4 == 0) // checks if year input has remainder of 0
            {
                printf("You have choosen a leap year!\n");
            }
            else
            {
                printf("You have not chosen a leap year!\n");
            }
            printf("\n");
            break;
        }
        
        case 'C':
        {
            int firstnumber;
            int secondnumber;
            int result;
            printf("Please Select 2 numbers!\n");
            printf("Enter First Number: ");
                scanf("%d",&firstnumber);
            printf("Enter second Number: ");
                scanf("%d",&secondnumber);
                printf("\n");
            result = firstnumber > secondnumber ? firstnumber : secondnumber; // checking to see if 1st number is bigger than 2nd number, if not then says the second value is larger
            printf("The larger number is %d\n",result); // prints number
            printf("\n");
            break;
        }
        
        case 'D':
        {
            int firstnumber;
            int secondnumber;
            float result;
            printf("Please Select 2 numbers!\n");
            printf("Enter First Number: ");
                scanf("%d",&firstnumber);
            printf("Enter second Number: ");
                scanf("%d",&secondnumber);
            printf("\n");
            
            if (secondnumber == 0) // checks if bottom number is 0
            {
                printf("You have picked 0 as your denominator, no result given!\n");
                break;
            }
            
            if (secondnumber != 0)
            {
                result = (float)firstnumber/(float)secondnumber; // doing division with type casted to float.
            }
            
            printf("the quotient to the two numbers is %.2f\n",result);// print results
            break;
        }
            
        default:
            printf("You have entered an invaild character, please try again...'%c'\n\n",option); // default case, print error
            break;
    }
}
