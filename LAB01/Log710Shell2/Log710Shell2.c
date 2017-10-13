 /***********************************************************************
* FILENAME : Log710Shell2.c 
*
* DESCRIPTION : Lab part 3
* 				The Shell must manage commands sent as background task.
* 				The Shell must wait for all background tasks to finish before exiting.
* 				The Shell must manage the "aptaches" command which lists all ongoing background tasks.
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
*     1.0   25/09/2017  TC & MN     Added Background structure, list of process and process manager. 
*     1.1   03/10/2017  TC & MN     Added trim method.
* 									Added create background process method.
*     1.2   10/10/2017  TC & MN     Fixed bug when creating process (all process had the same adress) .
* 									Remove background process from the list when it finishes.
*                                   Fixed bug for wallclock for background process.
*     1.3   11/10/2017  TC & MN     Added a signal handler to manage child death.
*                                   Added a signal to remove wrong process if exec fail.
* 	  1.4	12/10/2017	TC & MN		Added the DOC.
* 									Formatted for release.
**/

#include "Log710Shell2.h"

struct BackgroundProcess* backgroundProcessList[MAX_BACKGROUNG_PROCESS];
int backgroundProcessListCounter = 0;

/**
 * @brief Overrides the default behavior of SIGCHLD.
 * @param sig Signal ID
 */
void sig_handler(int sig) {
    if(DEBUG) {
        printf("sig_handler, child died sig received: %d\n", sig);
        fflush(stdout);
    }
    
    checkBackgroundProcess();
}

/**
 * @brief Registers all signal handlers.
 */
void registerSignalHandler() {
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sig_handler;

    sigaction(SIGCHLD, &sa, NULL);
}

int main(int argc, char **argv) {
    registerSignalHandler();
    executShell();
	
	return SUCCESS;
}

/**
 * @brief Main loop for the Shell execution.
 */
void executShell() {   
        
    while(TRUE) {
        // Display prompt
        int runInBackground = FALSE;
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
        if (inputArg[strlen(inputArg) - 1] == '\n') {
            inputArg[strlen(inputArg) - 1] = '\0';
        }
			
		// Remove &
		// Task to be executed in background
		if (inputArg[strlen(inputArg) - 1] == '&') {
            inputArg[strlen(inputArg) - 1] = '\0';
			runInBackground = TRUE;
		}
            
        // Trim the input to prevent executing empty command
        trim(inputArg);
            
        // Check if a command is provided by the user
        if (strlen(inputArg) == 0) {
            printf("A command must be specify in argument\n");
            fflush(stdout);
			
            continue;
        }
		
        // Check if task to be executed in background
        if (runInBackground) {
            struct BackgroundProcess* currentProcess = malloc(sizeof(struct BackgroundProcess));
            currentProcess->cmd = malloc(strlen(inputArg) * sizeof(char*));
            currentProcess->id = backgroundProcessListCounter+1;
			
            strcpy(currentProcess->cmd, inputArg);
            executeBackgroundProcess(currentProcess);
			
            continue;
        }
  
        // Create command
        char** cmd = getCmdArgs(inputArg);

        // Check if command has to be handled
        if (handleCommand(cmd) == TRUE)
            continue;
    
        executeCommand(cmd, runInBackground, NULL);
    }
}

/**
 * @brief Executes the command and creates a new process if needed.
 * @param cmd The command to execute
 * @param runInBackground Whether or not the command needs to be executed as a background task
 * @param currentProcess The process structure to execute as a background task
 */
void executeCommand(char** cmd, int runInBackground, struct BackgroundProcess* currentProcess) {
    if(DEBUG) {
        printf("executeCommand, arg cmd: %s, runInBackground: %d\n", cmd[0], runInBackground);
        fflush(stdout);
    }
    
    pid_t pid;
    switch(pid = fork()) {
        case -1:
            perror("An error occured during fork()\n");
            fflush(stderr);
			
            break;
        
        case 0 :
            childProcessFct(cmd);
			
            break;
            
        default:
            if(!runInBackground)
                parentProcessFct(pid);
            else if(runInBackground && currentProcess) {
                currentProcess->pid = pid; 
                struct timeval* time = malloc(sizeof(struct timeval));
                gettimeofday(time, NULL);
                currentProcess->startTime = time;
            }

            free(cmd);

            break;
    }
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
 * @brief Executes the command if it needs to be handled by the Shell.
 * @param cmd The command to execute
 * @return Whether or not the command was executed.
 */
int handleCommand(char** cmd) {
    if(DEBUG) {
        printf("handleCommand, arg cmd: %s\n", cmd[0]);
        fflush(stdout);
    }
    
    // EXIT
    if(strcmp(cmd[0], EXIT_COMMAND) == 0) {
        if(backgroundProcessListCounter > 0) {
            printf("Cannot exit now, there are %d tasks running in background. Waiting...\n", backgroundProcessListCounter);
            fflush(stdout);
            
            // Wait for all tasks to finish before exiting
            waitingBackgroundProcess();
        } 
        
        exit(0);
    } 
    
    // CD
    else if(strcmp(cmd[0], CD_COMMAND) == 0) {
        if (chdir(cmd[1]) < 0) {
            printf("Cannot move to %s\n", cmd[1]);
			fflush(stdout);
        } else {
            char cwd[BUFFER_SIZE];
            getcwd(cwd, BUFFER_SIZE);
            printf("Current working diretory: %s\n", cwd);
            fflush(stdout);
        }
        
        return TRUE;
    } 
    
    // APTACHES
    else if(strcmp(cmd[0], APTACHES_COMMAND) == 0) {
        displayBackgroundProcess();
        
        return TRUE;
    }
	
	return FALSE;
}

/**
 * @brief Displays current background tasks.
 */
void displayBackgroundProcess() {
    if(backgroundProcessListCounter > 0) {
        for(int i = 0; i < backgroundProcessListCounter; i++) {
            struct BackgroundProcess* process = backgroundProcessList[i];
            printf("[%d] %d %s\n", process->id,process->pid, process->cmd);
            fflush(stdout);
        }
    } else {
        printf("No task in background\n");
        fflush(stdout);
    }
}

/**
 * @brief Waits for all background tasks to finish.
 */
void waitingBackgroundProcess() {    
    if(DEBUG) {
        printf("waitingBackgroundProcess\n");
        fflush(stdout);
    }
    
    displayBackgroundProcess();
    
    while(backgroundProcessListCounter > 0) {
        checkBackgroundProcess();
        sleep(2);
    }
}

/**
 * @brief Looks for finished background tasks and displays them.
 */
void checkBackgroundProcess() {
    if(DEBUG) {
        printf("checkBackgroundProcess backgroundProcessListCounter = %d\n", backgroundProcessListCounter);
        fflush(stdout);
    }
    
    if(backgroundProcessListCounter > 0) {
        for(int i = 0; i < backgroundProcessListCounter; i++) {
            struct BackgroundProcess* process = backgroundProcessList[i];
            
            if(DEBUG) {
                printf("\n Check process cmd:%s and pid: %d\n",process->cmd,process->pid);
                fflush(stdout);
            }
            
            pid_t pid;
            int status;
           
            if((pid = waitpid(process->pid, &status, WNOHANG)) == -1) {
                printf("Wait no hang error for pid %d and status; %d\n",pid, status);
                fflush(stdout);
            } else if (pid == 0) {
                if(DEBUG) {
                    printf("Child %d is still running \n",process->pid);
                    fflush(stdout);
                }
            } else {
                if(WIFEXITED(status)) {
                    if(DEBUG) {
                        printf("Background process executed\n");
                    }
                    
                    printf("\n[%d] %d %s\n",process->id, process->pid, process->cmd);
                    fflush(stdout);
                } else {
                    printf("\n[%d] %d %s - exited with status of %d\n",process->id, process->pid, process->cmd, WEXITSTATUS(status));
                    fflush(stdout);
                }
                
                displayCommandResult(*process->startTime);
                
                removeProcessAtIndexFromList(process, i);
            }
        }
    }
}

/**
 * @brief Removes the process from the list.
 * @param processToRemove The process to remove
 * @param index The process' index
 */
void removeProcessAtIndexFromList(struct BackgroundProcess* processToRemove, int index) {
    if(!processToRemove) {
        printf("Cannot remove process null\n");
        fflush(stdout);
		
        return;
    }
    
    if(DEBUG) {
        printf("removeProcessAtIndexFromList processToRemove pid = %d and index: %d\n", processToRemove->pid, index);
        fflush(stdout);
    }
    
    // Remove process and free memory               
    removeProcess(processToRemove); 
    
    // Move all tasks after the current task to free memory
    if(backgroundProcessListCounter > 1)
        reorgBackgroundProcessList(index);
    
    backgroundProcessListCounter--;
}

/**
 * @brief Shifts down all processes from the end to the given index.
 * @param index The index
 */
void reorgBackgroundProcessList(int index) {
    if(DEBUG) {
        printf("reorgBackgroundProcessList, index: %d\n", index);
        fflush(stdout);
    }
    
    // Verify index is valid
    if(index < 0) {
        printf("Cannot reorg background process list from index: %d", index);
        fflush(stdout);
		
        return;
    }
    
    for(int i = index; i < backgroundProcessListCounter - 1; i++)
        backgroundProcessList[i] = backgroundProcessList[i+1];
    
    printf("Remove last element after reorg array of process\n");
    fflush(stdout);
	
    backgroundProcessList[backgroundProcessListCounter-1] = 0;
}

/**
 * @brief Removes a process from memory.
 * @param process The process to remove
 */
void removeProcess(struct BackgroundProcess* process) {
    if(DEBUG) {
        printf("removeProcess\n");
        fflush(stdout);
    }
    
    free(process->startTime);
    free(process->cmd);
    free(process);
}

/**
 * @brief Register and Execute the command as a background task.
 * @param currentProcess The process to execute
 */
void executeBackgroundProcess(struct BackgroundProcess* currentProcess) {
    if(DEBUG) {
        printf("executeBackgroundProcess\n");
        fflush(stdout);
    }
    
     // If a current process is not null, we need to add it to the background process list
    if(currentProcess) { 
        if(backgroundProcessListCounter == MAX_BACKGROUNG_PROCESS) {
            printf("Cannot add process to background process list, no more space\n");
            fflush(stdout);
        } else {
            backgroundProcessList[backgroundProcessListCounter] = currentProcess;
            backgroundProcessListCounter++;

            // Create command
            char** cmd = getCmdArgs(currentProcess->cmd);
            executeCommand(cmd, TRUE, currentProcess);

            printf("[%d] %d\n", currentProcess->id, currentProcess->pid);
            fflush(stdout);
        }
    }   
}

/**
 * @brief Waits for the child process to be finished and displays it.
 * @param pid Child's process ID
 */
void parentProcessFct(pid_t pid) {
    if(DEBUG) {
        printf("parentProcessFct\n");
        fflush(stdout);
    }
    
    struct timeval startTime;
    gettimeofday(&startTime, NULL);
        
    int status;
    waitpid(pid, &status, 0);
    
    displayCommandResult(startTime);
}

/**
 * @brief Displays a command's results.
 * @param startTime The command's time at which it started
 */
void displayCommandResult(struct timeval startTime) {
    if(DEBUG) {
        printf("displayCommandResult\n");
        fflush(stdout);
    }
    
    struct timeval endTime;
    gettimeofday(&endTime, NULL);
    
    struct rusage usage;
    // Get statistics for child of the calling process 
    if(getrusage(RUSAGE_CHILDREN, &usage) != 0){
        perror("An error occured during getrusage()\n"); 
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
    if(DEBUG) {
        printf("getWallClockTime\n");
        fflush(stdout);
    }
    
    long microseconds = (endTime->tv_sec - startTime->tv_sec) * (long)1000000 + ((long) endTime->tv_usec - (long) startTime->tv_usec);
    
    wallClockTime->tv_sec = microseconds / (long) 1000000;
    wallClockTime->tv_usec = microseconds % (long) 1000000;
}

/**
 * @brief Displays stats about execution process for a given usage Struct.
 * @param wcTime Time's Struct
 * @param usage Usage's Struct
 */
void displayStats(struct timeval* wcTime, struct rusage* usage) {
    if(DEBUG) {
        printf("displayStats\n");
        fflush(stdout);
    }
    
    // Display stats of execution.
    printf("+-----\n");
    printf("| Temps Wallclock : %li seconds, %li microseconds\n", wcTime->tv_sec , wcTime->tv_usec / (long) 1000); /*  user CPU time used */
    printf("| Temps CPU : %li seconds, %li microseconds\n", usage->ru_stime.tv_sec, usage->ru_stime.tv_usec / (long) 1000); /* system CPU   time used */
    printf("| Commutation de context involontaire : %li\n", (usage->ru_nivcsw)); /* involuntary context switches */
    printf("| Commutation de context volontaire : %li\n", (usage->ru_nvcsw)); /* voluntary context switches */
    printf("| Defaults de pages : %li\n", usage->ru_majflt); /* page faults (hard page faults) */
    printf("| Pages reclamees : %li\n", usage->ru_minflt); /* page reclaims (soft page faults) */
    printf("+-----\n");
    fflush(stdout);
}

/**
 * @brief Retrieves the command's arguments.
 * @param inputArgs The full command
 * @return The command's arguments.
 */
char** getCmdArgs(char* inputArgs) {
    if(DEBUG) {
        printf("getCmdArgs, inputArgs: %s\n", inputArgs);
        fflush(stdout);
    }
    
    char* inputCopy = (char*) malloc(strlen(inputArgs) * sizeof(char*));
    char separator[2] = " ";
    char* tmp; 
    char* token; 
    int count = 0;
	
    // Count elements
    strcpy(inputCopy, inputArgs);
    tmp = strtok(inputCopy, separator);
    while(tmp != NULL) {
        count++;
        tmp = strtok(NULL, separator);
    }

    // Create args
    char** arg = calloc (count + 1, sizeof(char*));
    
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
void* trim(char* stringToTrim) {
    if(DEBUG) {
        printf("trim, stringToTrim: %s\n", stringToTrim);
        fflush(stdout);
    }
    
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
		for(dest=0; src < len; dest++, src++) {
			stringToTrim[dest] = stringToTrim[src];
			stringToTrim[src] = '\0';
		}

    // Remove right whitespaces
    for(dest = len-  1; isspace(stringToTrim[dest]); --dest)
        stringToTrim[dest] = '\0';
        
    return stringToTrim;
}