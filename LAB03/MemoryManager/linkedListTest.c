 /***********************************************************************
* FILENAME : linkedListTest.c 
*
* DESCRIPTION : Lab 03
* 				Test file to test linkedList method.

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
*     1.0   13/11/2017  TC & MN     Create file and first implementation. 
* 
*
*/

#include <stdio.h>
#include "logger.h"
#include "linkedList.h"

/**
 * @brief Display all node in the specified list
 * @param list - list to print
 */
void printElement(struct linkedList_type* list);

/**
 * @brief Display information about a node
 * @param list - The list which contains the node
 * @param index - index of the node to display informations
 */
void displayNode(struct linkedList_type* list, int index);

/**
 * @brief 
 * @return 
 */
void linkedListTest()
{
    struct linkedList_type* linkedList = linkedListCreator(&linkedList);
    
    printElement(linkedList);
    
    int element0 = 0;
    int element1 = 10;
    int element2 = 3;
    int element3 = 4;
    int element4 = 2;
    int element5 = 5;
    
    int* p0 = &element0;
    int* p1 = &element1;
    int* p2 = &element2;
    int* p3 = &element3;
    int* p4 = &element4;
    int* p5 = &element5;
    
    removeElementAt(linkedList, 0);
    
    addElement(linkedList, p1);
    addElement(linkedList, p2);
    addElement(linkedList, p3);
    addElementAt(linkedList, p4, 1);
    addElementAt(linkedList, p5, 4);
    addElementAt(linkedList, p0, 0);
    
    removeElementAt(linkedList, -1);
    
    printElement(linkedList);
    printf("\n");
    fflush(stdout);
    
    displayNode(linkedList, -1);
    displayNode(linkedList, 0);
    displayNode(linkedList, 1);
    displayNode(linkedList, 2);
    displayNode(linkedList, 3);
    displayNode(linkedList, 4);
    displayNode(linkedList, 5);
    displayNode(linkedList, 6);
    
    removeElementAt(linkedList, 4);
    displayNode(linkedList, 3);
    displayNode(linkedList, 4);
    displayNode(linkedList, 5);
    displayNode(linkedList, 6);
    
    printf("\n");
    fflush(stdout);
    
    displayNode(linkedList, 0);
    removeElementAt(linkedList, 0);
    displayNode(linkedList, 0);
}


void displayNode(struct linkedList_type* list, int index){
    char debugMsg[128];
    struct node* nodeToDisplay = get(list, index);
    
    if(nodeToDisplay == NULL){
        sprintf(debugMsg, "Element at index %d is null", index);
        log(INFO, "main.c", debugMsg, __LINE__);
        return;
    }
    
    int* value = (int *) nodeToDisplay->element;
    sprintf(debugMsg, "Element at index %d is %d", index, *value);
    log(INFO, "main.c", debugMsg, __LINE__);
}

void printElement(struct linkedList_type* list){
    if(isEmpty(list)){
        log(INFO, "main.c", "List is empty", __LINE__);
    } else {
        char debugMsg[64];
        sprintf(debugMsg, "There are %d element", list->size);
        log(INFO, "main.c", debugMsg, __LINE__);
            
        struct node* currentNode = list->head;
        int index = 0;

        while(list->size > index){
            int* value = (int *) currentNode->element;
            sprintf(debugMsg, "Element at index %d is %d", index, *value);
            log(INFO, "main.c", debugMsg, __LINE__);
            currentNode = currentNode->next;
            index++;
        }
    }
}