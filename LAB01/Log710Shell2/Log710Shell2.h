#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

// Return code part
#define SUCCESS 0
#define ERROR_FORK 1
#define ERROR_EXECVP 2
#define ERROR_ARGS 3
#define ERROR_GETRUSAGE 4

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE  2048
#define MAX_BACKGROUNG_PROCESS 128
#define DEBUG 1

// Commands to manage
const char EXIT_COMMAND[5] = "exit";
const char CD_COMMAND[3] = "cd";
const char APTACHES_COMMAND[9] = "aptaches";
const char PROMPT[14] = "Log710A2017%>";

// Structure part
struct BackgroundProcess{
    int id;
    int pid;
    char* cmd;
    struct timeval* startTime;
};

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
 * @param currentProcess
 */
void executeBackgroundProcess(struct BackgroundProcess* currentProcess);

/**
 * @brief 
 * @param cmd
 * @param runInBackground
 */
void executeCommand(char *cmd, int runInBackground, struct BackgroundProcess* currentProcess);

/**
 * @brief 
 */
void parentProcessFct(pid_t pid);

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

/**
 * @brief 
 */
void checkBackgroundProcess();