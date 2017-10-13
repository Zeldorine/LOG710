 /***********************************************************************
* FILENAME : Log710Shell.c 
*
* DESCRIPTION :	Lab part 2
* 				The Shell must run on a loop.
* 				The Shell must manage the "exit" command.
* 				The Shell must manage the "cd" command.
*       
* EQUIPE : 8
*
* AUTHOR :
*       - Tony Cazorla
*       - Michael Nadeau      
* 
* START DATE :    25/09/2017
*
* CHANGES :
*
* VERSION   DATE        WHO         DETAIL
*     1.0   25/09/2017  TC & MN     Added main loop, input command, cd and exit commands. 
* 
*     1.1   03/10/2017  TC & MN     Added trim method.
* 
* 	  1.2	12/10/2017	TC & MN		Added the DOC.
*									Formatted for release.
* 
* 	  1.3	12/10/2017	TC & MN		Added exit when the command executed by the child fail.
**/

#include "Log710Shell.h"

int main(int argc, char** argv) 
{
    executShell();
	return SUCCESS;
}

/**
 * @brief Main loop for the Shell execution.
 */
void executShell() {
    while(TRUE) {
        // Display prompt
        printf(PROMPT);
        fflush(stdout);
        
                // Get command
        char inputArg[BUFFER_SIZE] = "";
        char *resultReadCmd = fgets(inputArg, BUFFER_SIZE, stdin);
        
        // Continue if fgets return an error
        if(!resultReadCmd){ 
            continue;
        }
        
        // Remove \n
        if (inputArg[strlen(inputArg) - 1] == '\n')
            inputArg[strlen(inputArg) - 1] = '\0';
            
        // Trim the input to prevent to execut empty command
        trim(inputArg);
        
        // Checks args before to process to make sure a command is provided by the user
        if (strlen(inputArg) == 0) {
            printf("A command must be specify in argument\n");
            fflush(stdout);
			
            continue;
        }
        
        // Create command
        char** cmd = getCmdArgs(inputArg);
        
        // Verify if execute command in parent
        if(handleCommand(cmd) == TRUE)
            continue;
        
        pid_t pid;
        
        switch(pid = fork()) {
            case -1:
                printf("An error occured during fork()");
                fflush(stderr);
                break;
            
            case 0 :
                childProcessFct(cmd);
                break;
                
            default:
                parentProcessFct(pid);
                break;
        }
        
        free(cmd);
    }
}

/**
 * @brief Executes the command if it needs to be handled by the Shell.
 * @param cmd The command to execute
 * @return Whether or not the command was executed.
 */
int handleCommand(char** cmd) {
    if(strcmp(cmd[0], EXIT_COMMAND) == 0)
        exit(0);
    else if(strcmp(cmd[0], CD_COMMAND) == 0) {
        if (chdir(cmd[1]) < 0) {
            printf("Cannot move to %s\n", cmd[1]);
			fflush(stdout);
        } else {
            char cwd[BUFFER_SIZE];
            
            if(getcwd(cwd, BUFFER_SIZE) == NULL){
                printf("An error occured while getting current working directory\n");
            } else {
                printf("Current working diretory: %s\n", cwd);
            }
            
			fflush(stdout);
        }
        
        return TRUE;
    }
	
	return FALSE;
}

/**
 * @brief Executes the command as a child process.
 * @param cmd The command to execute
 */
void childProcessFct(char** cmd) {
    execvp(cmd[0], &cmd[0]);
    
    // Display the wrong command
	printf("\nAn error occured while executing execvp, the command ");

    for(int i = 0; cmd[i] != '\0'; i++)
        printf("%s ", cmd[i]);

    printf("doesn't exist\n");
    fflush(stdout);
	
    free(cmd);
    
    exit(-1);
}

/**
 * @brief Waits for the child process to be finished and displays it.
 * @param pid Child's process ID
 */
void parentProcessFct(pid_t pid) {
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);
        
	int status;
    waitpid(pid, &status, 0);
    
    gettimeofday(&endTime, NULL);
    
    struct rusage usage;
    // Get statistics for child of the calling process 
    if(getrusage(RUSAGE_CHILDREN, &usage) != 0) {
        printf("An error occured during getrusage()");
		fflush(stderr);
	}
    
    struct timeval wcTime;
    getWallClockTime(&wcTime, &startTime, &endTime);
    
    displayStats(&wcTime, &usage);
}

/**
 * @brief Gets the wallclock time.
 * @param wallClockTime The time's structure
 * @param startTime Time at which it started
 * @param endTime Time at which it ended
 */
void getWallClockTime(struct timeval* wallClockTime, struct timeval* startTime, struct timeval* endTime) {
    long microseconds = (endTime->tv_sec - startTime->tv_sec) * (long)1000000 + ((long)endTime->tv_usec - (long)startTime->tv_usec);
    
    wallClockTime->tv_sec = microseconds / (long)1000000;
    wallClockTime->tv_usec = microseconds % (long)1000000;
}

/**
 * @brief Displays stats about execution process for a given usage Struct.
 * @param wcTime Time's Struct
 * @param usage Usage's Struct
 */
void displayStats(struct timeval* wcTime, struct rusage* usage) {
	// Display stats of execution.
    printf("+-----\n");
    printf("| Temps Wallclock : %li seconds, %li microseconds\n", wcTime->tv_sec , wcTime->tv_usec / (long) 1000); /*  user CPU time used */
    printf("| Temps CPU : %li seconds, %li microseconds\n", usage->ru_stime.tv_sec, usage->ru_stime.tv_usec / (long) 1000); /* system CPU time used */
    printf("| Commutation de context involontaire : %li\n", (usage->ru_nivcsw)); /* involuntary context switches */
    printf("| Commutation de context volontaire : %li\n", (usage->ru_nvcsw)); /* voluntary context switches */
    printf("| Defaults de pages : %li\n", usage->ru_majflt); /* page faults (hard page faults) */
    printf("| Pages reclamees : %li\n", usage->ru_minflt); /* page reclaims (soft page faults) */
    printf("+-----\n");
}

/**
 * @brief Retrieves the command's arguments.
 * @param inputArgs The full command
 * @return The command's arguments.
 */
char** getCmdArgs(char* inputArgs) {
    char* inputCopy = (char*) malloc(strlen(inputArgs) * sizeof(char*));
    char separator[2] = " ";
    char* tmp; 
    char* token; 
    int count = 0;
    
    // Count nb element
    strcpy(inputCopy, inputArgs);
    tmp = strtok(inputCopy, separator);
    while(tmp != NULL) {
        count++;
        tmp = strtok(NULL, separator);
    }

    //Create args
    char **arg = calloc (count + 1, sizeof(char*));
    
    strcpy(inputCopy, inputArgs);
    token = strtok(inputCopy, separator);
    int index = 0;
    while(token != NULL) {
        arg[index] = (char*) malloc(sizeof(token));
		strcpy(arg[index], token);
        token = strtok(NULL, separator);
        index++;
    }

	arg[index] = NULL;
	
    free(inputCopy);
    free(token);
    free(tmp);
    
   return arg;
}

/**
 * @brief Trims the string.
 * @param stringToTrim The string to trim
 */
char* trim(char* stringToTrim) {
    int dest;
    int src = 0;
    int len = strlen(stringToTrim);

    // Check if null
    if(!stringToTrim)
        return NULL;

    // Remove left whitespaces
    while(isspace(stringToTrim[src]))
		src++;

    if(strlen(stringToTrim) == 0)
        return stringToTrim;

    // Copy the rest of the string to front of string and remove the last
    if(src > 0) 
		for(dest=0; src<len; dest++, src++) 
        {
            stringToTrim[dest] = stringToTrim[src];
            stringToTrim[src] = '\0';
        }

    // Remove right whitespaces
    for(dest=len-1; isspace(stringToTrim[dest]); --dest)
        stringToTrim[dest] = '\0';
        
    return stringToTrim;
}
