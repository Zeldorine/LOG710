 /***********************************************************************
* FILENAME : logger.h
*
* DESCRIPTION : Lab 03
* 				Implementing a logger to keep a trace.

*       
* EQUIPE : 8
* 
* AUTHOR :
*       - Tony Cazorla
*       - Michael Nadeau      
* 
* START DATE :    13/11/2017
*
* CHANGES :
*
* VERSION   DATE        WHO         DETAIL
*     1.0   13/11/2017  TC & MN     Create a file and log the text. 
* 
*
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "logger.h"

FILE* logFile = NULL;

void initLogger(){
    char* timestamp = getTimestamp();
    char* name = malloc(strlen(APPENDIX) + strlen(timestamp) + strlen(FILE_TYPE) + 1);
    
    strcpy(name, APPENDIX);
    strcat(name, timestamp);
    strcat(name, FILE_TYPE);
        
    logFile = fopen(name, "w+");
}

char* getTimestamp(){
    time_t current_time;
    char* c_time_string;

    /* Obtain current time. */
    current_time = time(NULL);

    if (current_time == ((time_t)-1))
    {
        (void) fprintf(stderr, "Failure to obtain the current time.\n");
        return "";
    }

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

    if (c_time_string == NULL)
    {
        (void) fprintf(stderr, "Failure to convert the current time.\n");
        return "";
    }
    
    // Remove \n
    if (c_time_string[strlen(c_time_string) - 1] == '\n') {
        c_time_string[strlen(c_time_string) - 1] = '\0';
    }
    
    return c_time_string;
}

void closeLogger(){
    if(logFile != NULL){
        fclose(logFile);
    }
}

void log(int level, const char* tag, const char* message, int lineNumber){
    if(logFile == NULL) {
        return;
    }
    
    char constructTag[64];
    sprintf(constructTag, "%s - %d", tag, lineNumber);
    
    char* levelText;
    
    if(level == INFO){
        levelText = malloc(strlen(INFO_TEXT));
        levelText = INFO_TEXT;
    } else if (level == ERROR) {
        levelText = malloc(strlen(ERROR_TEXT));
        levelText = ERROR_TEXT;
    } else {
        levelText = malloc(strlen(DEFAULT_TEXT));
        levelText = DEFAULT_TEXT;
    }
        
    char* timestamp = getTimestamp();
    char* toLog = malloc(strlen(levelText) + strlen(timestamp) + strlen(TAB) + strlen(constructTag) + strlen(TAB) + strlen(message) + strlen(NEWLINE) + 1);

    
    strcpy(toLog, levelText);
    strcat(toLog, timestamp);
    strcat(toLog, TAB);
    strcat(toLog, constructTag);
    strcat(toLog, TAB);
    strcat(toLog, message);
    strcat(toLog, NEWLINE);
    
    printf("%s", toLog);
    fflush(stdout);
    fprintf(logFile, "%s", toLog);
}