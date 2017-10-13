#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>  // For function isspace()

// DEFINE PART
#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE  2048

// RETURN CODE 
#define SUCCESS 0
#define ERROR_FORK 1
#define ERROR_EXECVP 2
#define ERROR_ARGS 3
#define ERROR_GETRUSAGE 4


// COMMAND TO MANAGE
const char EXIT_COMMAND[5] = "exit";
const char CD_COMMAND[3] = "cd";

const char PROMPT[15] = "Log710A2017%%>";

// FUNCTION PART

/**
 * @brief Main loop for the Shell execution.
 */
void executShell();

/**
 * @brief Executes the command if it needs to be handled by the Shell.
 * @param cmd The command to execute
 * @return Whether or not the command was executed.
 */
int handleCommand(char** cmd);
 
/**
 * @brief Executes the command as a child process.
 * @param cmd The command to execute
 */
void childProcessFct(char** cmd);

/**
 * @brief Waits for the child process to be finished and displays it.
 * @param pid Child's process ID
 */
void parentProcessFct(pid_t pid);

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
char* trim(char* stringToTrim);
