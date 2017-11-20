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
#include "common.h"
#include "logger.h"
#include "linkedList.h"

int main(int argc, char **argv)
{
	initLogger();
    
    log(INFO, "main", "LOG710 - LAB03 - MEMORY MANAGER \n", __LINE__);
    
    struct linkedList_type* linkedList = linkedListCreator(&linkedList);
    

    
    closeLogger();
   
	return 0;
}
