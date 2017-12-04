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
#include "allocationStrategyTest.h"

/**
 * @brief 
 */
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
    
    alloumem(8);
    struct memoryBloc* bloc2 = alloumem(8);
    alloumem(16);
    struct memoryBloc* bloc4 = alloumem(6);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    liberemem(bloc2);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    liberemem(bloc4);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    alloumem(16);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    closeLogger();
}

/**
 * @brief 
 */
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
    
    alloumem(16);
    struct memoryBloc* bloc2 = alloumem(32);
    alloumem(256);
    alloumem(4);
    struct memoryBloc* bloc5 = alloumem(64);
    alloumem(4);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    liberemem(bloc2);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    liberemem(bloc5);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    alloumem(24);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    closeLogger();
}