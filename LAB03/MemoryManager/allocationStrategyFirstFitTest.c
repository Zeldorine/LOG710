 /***********************************************************************
* FILENAME : allocationStrategyFirstFitTest.c 
*
* DESCRIPTION : Lab 03
* 				Test file to test first fit method.

*       
* EQUIPE : 8
* 
* AUTHOR :
*       - Tony Cazorla
*       - Michael Nadeau      
* 
* START DATE :    27/11/2017
*
* CHANGES :
*
* VERSION   DATE        WHO         DETAIL
*     1.0   27/11/2017  TC & MN     Create file and first implementation. 
* 
*
*/
#include <stdio.h>
#include "logger.h"
#include "linkedList.h"
#include "allocationStrategy.h"

void testFirstFit(){
    initLogger();
    
    log(INFO, "main", "LOG710 - LAB03 - MEMORY MANAGER \n", __LINE__);
    log(INFO, "main", "LOG710 - LAB03 - TEST FIRST FIT ALGORITHM \n", __LINE__);
    
    struct linkedList_type* linkedList = linkedListCreator(&linkedList);
    
    if(linkedList == NULL){
        log(ERROR, "main", "main is null \n", __LINE__);
    }
    
    initmem(32);
    alloumem(64);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    struct memoryBloc* bloc1 = alloumem(8);
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

void testFirstFit2(){
    initLogger();
    
    log(INFO, "main", "LOG710 - LAB03 - MEMORY MANAGER \n", __LINE__);
    log(INFO, "main", "LOG710 - LAB03 - TEST FIRST FIT ALGORITHM \n", __LINE__);
    
    struct linkedList_type* linkedList = linkedListCreator(&linkedList);
    
    if(linkedList == NULL){
        log(ERROR, "main", "main is null \n", __LINE__);
    }
    
    initmem(128);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    struct memoryBloc* bloc1 = alloumem(16);
    struct memoryBloc* bloc2 = alloumem(32);
    struct memoryBloc* bloc3 = alloumem(256);
    struct memoryBloc* bloc4 = alloumem(4);
    struct memoryBloc* bloc5 = alloumem(64);
    struct memoryBloc* bloc6 = alloumem(4);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    liberemem(bloc2);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    liberemem(bloc5);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    bloc3 = alloumem(24);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    closeLogger();
   
	return 0;
}