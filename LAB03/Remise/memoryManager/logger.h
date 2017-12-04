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

#define INFO_TEXT  "[INFO]"
#define ERROR_TEXT "[ERROR]"
#define DEFAULT_TEXT "[DEFAULT]"

#define APPENDIX "Log710_Lab03_log_"
#define FILE_TYPE ".txt"
#define TAB "\t"
#define NEWLINE "\n"

#define ERROR  1
#define INFO  0

/**
 * @brief Init the logger and create a file Log710_Lab03_log_[actualTimestamp].txt 
 */
void initLogger();

/**
 * @brief Close the logger and close the file
 */
void closeLogger();

/**
 * @brief Get the actual timestamp
 * @return the actual timestamp
 */
char* getTimestamp();

/**
 * @brief Log a message
 * @param level - One of the message level identifiers, e.g., INFO
 * @param tag - A tag to identify th elog, for instance : the class name
 * @param message - The string message
 * @param lineNumber - The line in the code to retrieve the line
 */
void log(int level, const char* tag, const char* message, int lineNumber);