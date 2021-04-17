/*
* Program Title: movies_by_year
* Class: CS 344
* Date: 4/19/2021
* Name: Alexander Prestwich
* Description: Program reads data from file specified by user
*				through menu options. Program will process
*				files using C directory commands
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>

void largest_movie() {
	
}

int main(int argc, char* argv[])
{

    /* read in data from file and process */
    //struct movie* list = processFile(argv[1]);
    
    char strUserChoice[2];
    int intUserChoice;

    while (true) {
        /* present user menu and read input */
        printf("\n1. Select file to process\n");
        printf("2. Exit the program\n");
        printf("\nEnter a choice from 1 or 2: ");

        /*  read user input */
        fgets(strUserChoice, 2, stdin);
        /* remove '\n' from input stream before reading user input */
        char c = getchar();
        /* not checking data type here as Assignment explicitly says input will be integer */
        intUserChoice = atoi(strUserChoice);

        switch (intUserChoice) {
            case 1:
            {
            	printf("Which file do you want to process?\n");
            	printf("Enter 1 to pick the largest file\n");
            	printf("Enter 2 to pick the smallest file\n");
            	printf("Enter 3 to specify the name of a file\n");
            	printf("\nEnter a choice from 1 to 3: ");

            	char strProcessChoice[2];
            	int processChoice;
            	fgets(strProcessChoice, 2, stdin);
       			/* remove '\n' from input stream before reading user input */
        		char c = getchar();
        		/* not checking data type here as Assignment explicitly says input will be integer */
        		intUserChoice = atoi(strUserChoice);


            }
                break;
            case 2:
            	return EXIT_SUCCESS;
                break;
            default:
                /* error message reprompt*/
                printf("You entered an incorrect choice. Try Again.\n");
                break;
        }

        
    }

    /* free all memory */
    //struct movie* tmp;
    //while (list != NULL)
    //{
    //    tmp = list;
    //    list = list->next;
    //    free(tmp->title);
    //    free(tmp->year);
    //    free(tmp->languages);
    //    free(tmp->rating);
    //    free(tmp);
    //}

    return EXIT_SUCCESS;
}