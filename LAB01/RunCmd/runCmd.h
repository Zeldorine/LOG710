#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

#include "string.h"

// Return code part

int SUCCESS = 0;
int ERROR_FORK = 1;
int ERROR_EXECVP = 2;
int ERROR_ARGS = 3;
int ERROR_GETRUSAGE = 4;

// Function part

/**
 * @brief Executes the command as a child process.
 * @param cmd The command to execute
 */
void childProcessFct(char** argv);

/**
 * @brief Waits for the child process to be finished and displays it.
 */
void parentProcessFct();

/**
 * @brief Sets clock time.
 * @param wallClockTime The time's structure
 * @param startTime Time at which it started
 * @param endTime Time at which it ended
 */
void getWallClockTime(struct timeval* wallClockTime, struct timeval* startTime, struct timeval* endTime);

/**
 * @brief Displays time stats for a given usage Struct.
 * @param wcTime Time's Struct
 * @param usage Usage's Struct
 */
void displayStats(struct timeval* wcTime, struct rusage* usage);