 /***********************************************************************
* FILENAME : allocationStrategyNextFitTest.c 
*
* DESCRIPTION : Lab 03
* 				Test file to test next fit method.

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
void testNextFit(){
    log(INFO, "main", "LOG710 - LAB03 - MEMORY MANAGER", __LINE__);
    log(INFO, "main", "LOG710 - LAB03 - TEST NEXT FIT ALGORITHM \n", __LINE__);
    
    setAllocationStrategy(NEXT_FIT);
    initmem(128);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    log(INFO, "main.c", "\n\n", __LINE__);
    log(INFO, "main", "-----ALLOCATION DES BLOCS-----", __LINE__);
    alloumem(16);
    struct memoryBloc* bloc2 = alloumem(32);
    alloumem(256);
    alloumem(4);
    struct memoryBloc* bloc5 = alloumem(64);
    alloumem(4);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    log(INFO, "main.c", "\n\n", __LINE__);
    log(INFO, "main", "-----LIBERATION DES BLOCS-----", __LINE__);
    liberemem(bloc2);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    liberemem(bloc5);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
    
    log(INFO, "main.c", "\n\n", __LINE__);
    log(INFO, "main", "-----ALLOCATION D'UN BLOC DE 50 et de 6-----", __LINE__);
    alloumem(50);
    alloumem(6);
    
    affiche_etat_memoire();
    affiche_parametres_memoire(-1);
}