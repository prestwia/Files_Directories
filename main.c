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
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>


void largest_movie() {
	/* code adapted from 3_5_stat_example.c */
	/* open current directory */
	DIR * currDir = opendir(".");
	struct dirent *aDir;
	struct stat dirStat;

	char* maxFileName;
	int maxFileSize = 0;

	/* go through all entries */
	while((aDir = readdir(currDir)) != NULL) {
		/* check if file name begins with "movies_" */
		if(strncmp("movies_", aDir->d_name, strlen("movies_")) == 0) {
			/* get and check if file extension is .csv */
			char* extension;
			extension = strrchr(aDir->d_name, '.');
			/* check if extension exists, else seg fault */
			if (extension != NULL) {
				/* if extension is .csv get filename, and filesize */
				if (strcmp(extension, ".csv") == 0) {
					/* get metadata for current entry */
					stat(aDir->d_name, &dirStat);
					
					/* get largest filename and filesize */
				   	if (dirStat.st_size > maxFileSize) {
				   		maxFileSize = (dirStat.st_size);
				   		maxFileName = (aDir->d_name);
				   	}
                }	
			}
		}
	}
	
	printf("Now processing chosen file named %s\n", maxFileName);
	closedir(currDir);
}

void smallest_movie() {
	/* code adapted from 3_5_stat_example.c */
	/* open current directory */
	DIR * currDir = opendir(".");
	struct dirent *aDir;
	struct stat dirStat;

	char* minFileName;
	int minFileSize = INT_MAX;

	/* go through all entries */
	while((aDir = readdir(currDir)) != NULL) {
		/* check if file name begins with "movies_" */
		if(strncmp("movies_", aDir->d_name, strlen("movies_")) == 0) {
			/* get and check if file extension is .csv */
			char* extension;
			extension = strrchr(aDir->d_name, '.');
			/* check if extension exists, else seg fault */
			if (extension != NULL) {
				/* if extension is .csv get filename, and filesize */
				if (strcmp(extension, ".csv") == 0) {
					/* get metadata for current entry */
					stat(aDir->d_name, &dirStat);
					
					/* get largest filename and filesize */
				   	if (dirStat.st_size < minFileSize) {
				   		minFileSize = (dirStat.st_size);
				   		minFileName = (aDir->d_name);
				   	}
                }	
			}
		}
	}
	
	printf("Now processing chosen file named %s\n", minFileName);
	closedir(currDir);
}

void chosen_movie() {
	/* code adapted from 3_5_stat_example.c */
	printf("Enter file name to be processed: ");
	char chosenFileName[256];
	fgets(chosenFileName, 256, stdin);
	chosenFileName[strcspn(chosenFileName, "\n")] = 0;

    printf("Entered filename: %s\n", chosenFileName);
	/* open current directory */
	DIR * currDir = opendir(".");
	struct dirent *aDir;
	struct stat dirStat;

	char* processFile = NULL;

	/* go through all entries */
	while((aDir = readdir(currDir)) != NULL) {
		/* check if file name matches entered file name */
		if(strcmp(chosenFileName, aDir->d_name) == 0) {
			
			/* get metadata for current entry */
			stat(aDir->d_name, &dirStat);
			
			processFile = (aDir->d_name);
		}
	}
	
	if (processFile == NULL) {
		printf("No file named %s in directory\n", chosenFileName);
	}
	else {
		printf("Now processing chosen file named %s\n", processFile);
	}
	closedir(currDir);
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
        		processChoice = atoi(strProcessChoice);

        		switch (processChoice) {
        			case 1: 
        				largest_movie();
        				break;
        			case 2:
        				smallest_movie();
        				break;
        			case 3:
        				chosen_movie();
        				break;
        			default: 
        				break;
        		}
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