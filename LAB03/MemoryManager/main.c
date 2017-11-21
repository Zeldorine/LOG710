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
#include "allocationStrategy.h"

int main()
{
	initLogger();
    
    log(INFO, "main", "LOG710 - LAB03 - MEMORY MANAGER \n", __LINE__);
    
    struct linkedList_type* linkedList = linkedListCreator(&linkedList);
    
    if(linkedList == NULL){
        log(ERROR, "main", "main is null \n", __LINE__);
    }
    
    initmem(32);
    alloumem(64);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    struct memoryBloc* bloc1 = alloumem(16);
    struct memoryBloc* bloc2 = alloumem(8);
    struct memoryBloc* bloc3 = alloumem(16);
    struct memoryBloc* bloc4 = alloumem(6);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    liberemem(bloc2);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    liberemem(bloc4);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    bloc3 = alloumem(16);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    closeLogger();
   
	return 0;
}
