#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h> 

// DEFINE PART
#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE  2048
#define MAX_BACKGROUNG_PROCESS 128
#define DEBUG 0

// RETURN CODE 
#define SUCCESS 0
#define ERROR_FORK 1
#define ERROR_EXECVP 2
#define ERROR_ARGS 3
#define ERROR_GETRUSAGE 4

// COMMAND TO MANAGE
const char EXIT_COMMAND[5] = "exit";
const char CD_COMMAND[3] = "cd";
const char APTACHES_COMMAND[9] = "aptaches";

const char PROMPT[16] = "\nLog710A2017%%>";

// STRUCTURE PART
struct BackgroundProcess {
    int id;
    int pid;
    char* cmd;
    struct timeval* startTime;
};

// SIGNAL HANDLER PART

/**
 * @brief Overrides the default behavior of SIGCHLD.
 * @param sig Signal ID
 */
void sig_handler(int sig);

// FUNCTION PART

/**
 * @brief Registers all signal handlers.
 */
void registerSignalHandler();

/**
 * @brief Main loop for the Shell execution.
 */
void executShell();

/**
 * @brief Executes the command and creates a new process if needed.
 * @param cmd The command to execute
 * @param runInBackground Whether or not the command needs to be executed as a background task
 * @param currentProcess The process structure to execute as a background task
 */
void executeCommand(char** cmd, int runInBackground, struct BackgroundProcess* currentProcess);
 
/**
 * @brief Executes the command as a child process.
 * @param cmd The command to execute
 */
void childProcessFct(char** cmd);

/**
 * @brief Executes the command if it needs to be handled by the Shell.
 * @param cmd The command to execute
 * @return Whether or not the command was executed.
 */
int handleCommand(char** cmd);
 
/**
 * @brief Displays current background tasks.
 */
void displayBackgroundProcess();
 
/**
 * @brief Waits for all background tasks to finish.
 */
void waitingBackgroundProcess();

/**
 * @brief Looks for finished background tasks and displays them.
 */
void checkBackgroundProcess();

/**
 * @brief Removes the process from the list.
 * @param processToRemove The process to remove
 * @param index The process' index
 */
void removeProcessAtIndexFromList(struct BackgroundProcess* processToRemove, int index);

/**
 * @brief Shifts down all processes from the end to the given index.
 * @param index The index
 */
void reorgBackgroundProcessList(int index);

/**
 * @brief Removes a process from memory.
 * @param process The process to remove
 */
void removeProcess(struct BackgroundProcess* process);

/**
 * @brief Register and Execute the command as a background task.
 * @param currentProcess The process to execute
 */
void executeBackgroundProcess(struct BackgroundProcess* currentProcess);

/**
 * @brief Waits for the child process to be finished and displays it.
 * @param pid Child's process ID
 */
void parentProcessFct(pid_t pid);

/**
 * @brief Displays a command's results.
 * @param startTime The command's time at which it started
 */
void displayCommandResult(struct timeval startTime);
 
/**
 * @brief Gets the wallclock time.
 * @param wallClockTime The time's structure
 * @param startTime Time at which it started
 * @param endTime Time at which it ended
 */
void getWallClockTime(struct timeval* wallClockTime, struct timeval* startTime, struct timeval* endTime);

/**
 * @brief Displays stats about execution process for a given usage Struct.
 * @param wcTime Time's Struct
 * @param usage Usage's Struct
 */
void displayStats(struct timeval* wcTime, struct rusage* usage);

/**
 * @brief Retrieves the command's arguments.
 * @param inputArgs The full command
 * @return The command's arguments.
 */
char** getCmdArgs(char* argv);

/**
 * @brief Trims the string.
 * @param stringToTrim The string to trim
 */
void* trim(char* stringToTrim);
