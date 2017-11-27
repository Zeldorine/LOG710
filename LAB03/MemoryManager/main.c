 /***********************************************************************
* FILENAME : main.c
*
* DESCRIPTION : Lab 03
* 				Entry point.

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
*     1.0   13/11/2017  TC & MN      
* 
*
*/

#include <stdio.h>
#include "logger.h"
#include "linkedList.h"
#include "allocationStrategy.h"

int main()
{
    testFirstFit();
    printf("\n\n");
    fflush(stdout);
    
    testFirstFit2();
    printf("\n\n");
    fflush(stdout);
    
    testBestFit();
    printf("\n\n");
    fflush(stdout);
    
    testWorstFit();
    printf("\n\n");
    fflush(stdout);
    
    testNextFit();
}