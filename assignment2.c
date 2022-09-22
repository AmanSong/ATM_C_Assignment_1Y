/*
Aman Song
21/02/2021
This is a program for security authentication based on a 4 digit access code.
This program allows the user to enter a 4 digit code, they can then 
encrypt said code and compare it to the authorised access code, decrypt the previously entered code, display how many times code entered was successful or not
and finnally the program should terminate gracefully when desired.

*important separate function for each call, pointer notation only, functions must use pass by reference.
*/

#include <stdio.h>
#define SIZE 4

int* case1(void);
int* case2(int[]);
int* case3(int[]);
void case4(int[]);
void case5(void);

int main()
{
    int menu = 0;
    int i = 0;
    int *code;
    int confirm = 0;
    int show = 0;
    int *attempts;
    char error;

    do //start of do while loop
    {
        //clears menu
        menu = 0;

        //deference pointer
        int *code;

        printf("\n------------------------------------------");
        printf("\nPlease choose one of the following options\n");
        printf("1 - Enter in access code\n");
        printf("2 - Encrypt access code and verify\n");
        printf("3 - Decrypt code entered\n");
        printf("4 - Display successful/unsuccessful attempts\n");
        printf("5 - Exit program\n");
        printf("------------------------------------------\n");
        scanf("%d", &menu);

        //catches any invalid characters entered to prevent an infinite loop
        error = getchar();

        switch (menu)
        {
            case(1):
            {
                code = case1();

                printf("You have entered\n");
                for (i = 0; i < SIZE; i++)
                {
                    printf("%d ", *(code + i));
                }

                //confirms that code was entered
                confirm = 1;
                //current fix for a bug if user did not encrypt code beforehand and chooses this option first which closes program
                show = 1;

                break;
            }//end of case 1

            case(2):
            {
                //breaks user out if no code was entered
                if (confirm != 1)
                {
                    printf("No access code entered\n");
                    break;
                }

                //deference attempts
                *attempts;

                attempts = case2(code);

                //confirmed that code has been encrypted
                confirm = 2;

                break;
            }//end of case 2

            case(3):
            {
                //breaks user out if they did not encrypt their code
                if (confirm != 2)
                {
                    printf("No code was entered or code was not encrypted yet\n");
                    printf("Or you had already decrypted this code\n");
                    break;
                }

                case3(code);

                //confirms that code has been decrypted
                confirm = 3;

                break;
            } //end of case 3

            case(4):
            {
                //current fix for if user did not encrypt code beforehand and chooses this option first which closes program
                if (show != 1)
                {
                    printf("\nNo attempts made yet\n");
                    break;
                }
                
                case4(attempts);
                break;
            }//end of case 4

            case(5):
            {
                char choice;

                printf("Do you want to exit the program?\n");
                printf("y/n\n");
                scanf("%c", &choice);

                if (choice == 'y')
                {
                    case5();
                    break;

                }
                else if (choice == 'n')
                {
                    menu = 0;
                    break;
                }
    
                break;
            }//end of case 5

            default:
            {
                printf("\nInvalid key entered\n");
                printf("Please re-enter you code and try again\n");

                //resets confirmation if user enters an invalid key to prevent bugs
                confirm = 0;
                break;
            }
        }

    } while (menu != 5); //end of do while loop
    

    return 0;

}//end of main

//case 1 function
int* case1(void)
{
    int i;
    static int code[SIZE];

    printf("Enter access code\n");

    for (i = 0; i < SIZE; i++)
    {
        scanf("%1d", &*(code + i));
    }
    
    return code;

}//end of case 1 function

//case 2 function
int* case2(int code[])
{
    int i;
    int temp = 0;
    int const access_code[SIZE] = {4,5,2,3};

    //hard coded 2 because there are only 2 values in the array.
    static int attempts[2];

    printf("\nEncrypting");

    //swap 1st digit with 3rd digit and add 1
    temp = *(code + 0);
    *(code + 0) = *(code + 2);
    *(code + 2) = temp;
    (*(code + 0))++;
    (*(code + 2))++;

    //swap 2nd digit with 4th digit and add 1
    temp = *(code + 1);
    *(code + 1) = *(code + 3);
    *(code + 3) = temp;
    (*(code + 1))++;
    (*(code + 3))++;

    //if the digit is equals to 10 then change it to 0
    for (i = 0; i < SIZE; i++)
    {
        if (*(code + i) == 10)
        {
            *(code + i) = 0;
        }
                    
    }
                
    //compare the encrypted code with the access_code
    if (code[0] == access_code[0] && code[1] == access_code[1] && code[2] == access_code[2] && code[3] == access_code[3])
    {
        printf("\nCorrect code entered\n");
        (*(attempts + 0))++;
    }
    else
    {
        printf("\nWrong code entered\n");
        (*(attempts + 1))++;
    }

    return attempts;

}//end of case 2 function

//case 3 function
int* case3(int code[])
{
    int temp;
    int i;

    //same as before but in reverse
    temp = *(code + 2);
    *(code + 2) = *(code + 0);
    *(code + 0) = temp;
    (*(code + 0))--;
    (*(code + 2))--;

    temp = *(code + 3);
    *(code + 3) = *(code + 1);
    *(code + 1) = temp;
    (*(code + 1))--;
    (*(code + 3))--;

    //if the digit equals to -1 then change to 9
    for (i = 0; i < SIZE; i++)
    {
        if (*(code + i) == -1)
        {
            *(code + i) = 9;
        }
                    
    }

    printf("\nDecrypting\n");
    printf("\nYour code was\n");

    for (i = 0; i < SIZE; i++)
    {
         printf("%d", *(code + i));
    }

}//end of case 3 function

//case 4 function
void case4(int attempts[])
{
    printf("\nYou have entered the access code\n");
    printf("%d times successfully\n", *(attempts + 0));
    printf("%d times unsuccessfully\n", *(attempts + 1));

}//end of case 4 function

//case 5 function
void case5(void)
{
    printf("\nClosing program\n");
    return;
}//end of case 5 function