#include <sys/time.h>
#include <sys/resource.h>

// Return code part
int SUCCESS = 0;
int ERROR_FORK = 1;
int ERROR_EXECVP = 2;
int ERROR_ARGS = 3;
int ERROR_GETRUSAGE = 4;

int TRUE=1;
int FALSE=0;
int BUFFER_SIZE = 2048;

// Commands to manage
char EXIT_COMMAND[5] = "exit";
char CD_COMMAND[3] = "cd";

// Function part

/**
 * @brief 
 */
void executShell();

/**
 * @brief 
 * @param cmd
 */
void childProcessFct(char **cmd);

/**
 * @brief 
 */
void parentProcessFct();

/**
 * @brief 
 * @param wallClockTime
 * @param startTime
 * @param endTime
 */
void getWallClockTime(struct timeval* wallClockTime, struct timeval* startTime, struct timeval* endTime);

/**
 * @brief 
 * @param argv
 * @return 
 */
char** getCmdArgs(char* argv);

/**
 * @brief 
 * @param cmd
 */
int handleCommand(char **cmd);

/**
 * @brief 
 * @param wcTime
 * @param usage
 */
void displayStats(struct timeval* wcTime, struct rusage* usage);

/**
 * @brief 
 * @param stringToTrim
 */
void *trim(char* stringToTrim);