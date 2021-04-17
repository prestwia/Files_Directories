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
#include <time.h>

/* struct for student information */
struct movie
{
    char* title;
    char* year;
    char* languages;
    char* rating;
    struct movie* next;
};

/* Parse the current line which is space delimited and create a
*  movie struct with the data in this line
*/
struct movie* createMovie(char* currLine)
{
    struct movie* currMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char* saveptr;

    // The first token is the title
    char* token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the year
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->year, token);

    // The next token is the languages
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->languages, token);

    // The last token is the rating
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->rating = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->rating, token);

    // Set the next node to NULL in the newly created student entry
    currMovie->next = NULL;

    return currMovie;
}


/*
* Return a linked list of students by parsing data from
* each line of the specified file.
*/
struct movie* makeList(char* filePath)
{
    // Open the specified file for reading only
    FILE* movieFile = fopen(filePath, "r");

    char* currLine = NULL;
    size_t len = 0;
    ssize_t nread;
    //char* token;
    int numMovies = 0;
    char* filename;

    // The head of the linked list
    struct movie* head = NULL;
    // The tail of the linked list
    struct movie* tail = NULL;

    // Read the file line by line
    while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {
        numMovies++;
        if (numMovies == 1) {
            continue;
        }

        // Get a new student node corresponding to the current line
        struct movie* newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }

    filename = basename(filePath);

    free(currLine);
    fclose(movieFile);
    return head;
}

/* 
*	Create new directory with prestwia.movies.(random).
*	Parse file and populate movies Linked List
*	Iterate through all movies and print titles of
*	movies of same year in file year.txt
*   Set year.txt permissions to rw-r-----
*/
void processFile(char* filename) {
	/* generate random num from 0 to 9999 inclusive */
	srand(time(0));
	int lower = 0;
	int upper = 99999;
	int randNum = (rand() % (upper - lower + 1));
	
	/* user random number to create directory name */
	char num[5];
	sprintf(num, "%d", randNum);
	char dirName[256];
	strcpy(dirName, "./prestwia.movies.");
	strcat(dirName, num);
	
	/* create new directory with name dirName */
	int result = mkdir(dirName, 0750);
	printf("Created directory with name %s\n", dirName);

	/* construct name of source file from parts above */
	char sourceFile[256];
	strcpy(sourceFile, "./");
	strcat(sourceFile, filename);

	struct movie* movieList = makeList(sourceFile);

	/* iterate through all movies */
	while (movieList != NULL) {
		/* construct path to new file year.txt */
		char newFile[256];
		strcpy(newFile, dirName);
		strcat(newFile, "/");
		strcat(newFile, movieList->year);
		strcat(newFile, ".txt");
		
		/* open file with append mode and write title */
		FILE *fp = fopen(newFile, "a");
		char fileString[100];
		strcpy(fileString, movieList->title);
		strcat(fileString, "\n");
		fprintf(fp, fileString);
		fclose(fp);
		/* set file permission to rw-r-----, or print error msg */
		if (chmod(newFile, 0640) != 0) {
			printf("chmod() error for file %s\n", newFile);
		}

		/* iterate to next movie */
		movieList = movieList->next;
	}

	/* free all memory */
    struct movie* tmp;
    while (movieList != NULL)
    {
        tmp = movieList;
        movieList = movieList->next;
        free(tmp->title);
        free(tmp->year);
        free(tmp->languages);
        free(tmp->rating);
        free(tmp);
    }
}

/* 
*	Find largest file in current directory
*	that is names movies_[].csv.
*	Process said file.
*/
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
	processFile(maxFileName);
	closedir(currDir);
}

/* 
*	Find smallest file in current directory
*	that is names movies_[].csv.
*	Process said file.
*/
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
	processFile(minFileName);
	closedir(currDir);
}

/* 
*	Find file that user enters in current directory.
*	Process said file.
*/
bool chosen_movie() {
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

	char* dirFile = NULL;

	/* go through all entries */
	while((aDir = readdir(currDir)) != NULL) {
		/* check if file name matches entered file name */
		if(strcmp(chosenFileName, aDir->d_name) == 0) {
			
			/* get metadata for current entry */
			stat(aDir->d_name, &dirStat);
			
			dirFile = (aDir->d_name);
		}
	}
	
	/* print error msg if file not found, else print processing msg */
	bool foundFile = false;
	if (dirFile == NULL) {
		printf("No file named %s in directory\n", chosenFileName);
		return true;
	}
	else {
		printf("Now processing chosen file named %s\n", dirFile);
		foundFile = true;
	}

	/* close directory */
	closedir(currDir);

	/* process file */
	if (foundFile)
		processFile(dirFile);

	return false;
}



int main(int argc, char* argv[])
{
    
    char strUserChoice[2];
    int intUserChoice;
    bool menuLoop = true;

    while (menuLoop) {
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
            	bool nestedMenu = true;
            	while(nestedMenu) {
	            	printf("\nWhich file do you want to process?\n");
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
	        				nestedMenu = false;
	        				break;
	        			case 2:
	        				smallest_movie();
	        				nestedMenu = false;
	        				break;
	        			case 3:
	        				nestedMenu = chosen_movie();
	        				break;
	        			default: 
	        				printf("You entered an incorrect choice. Try Again.\n");
	        				break;
	        		}
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


    return EXIT_SUCCESS;
}