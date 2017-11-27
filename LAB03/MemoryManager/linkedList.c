 /***********************************************************************
* FILENAME : linkedList.c 
*
* DESCRIPTION : Lab 03
* 				The data structure to save and manage memory bloc.

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
*     1.0   13/11/2017  TC & MN     Create list and first implementation of these methods :
*                                       - struct linkedList linkedList();
*                                       - int addElement(struct linkedList* list, void* element);
*                                       - int addElementAt(struct linkedList* list, void* element, int index);
*                                       - int removeElementAt(struct linkedList* list, int index);
*                                       - int removeElement(struct linkedList* list, void* element);
*                                       - void* get(struct linkedList* list, int index);
*                                       - int isEmpty(struct linkedList* list);
*                                       - int isFull(struct linkedList* list);
*                                       - int size(struct linkedList* list);
*                                       - void printElement(struct linkedList* list);
* 
*     1.1   20/11/2017  TC & MN     Add an attribut to keep the last node added
* 
* 
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

struct linkedList_type* linkedListCreator(){    
    log(INFO, "linkedList.c ", "Enter - create a new list", __LINE__);
    
    struct linkedList_type* list = malloc(sizeof(struct linkedList_type));
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    log(INFO, "linkedList.c", "Exit - create a new list", __LINE__);

    return list;
}

int addElement(struct linkedList_type* list, void* element){
    return addElementAt(list, element, list->size);
}

int addElementAt(struct linkedList_type* list, void* element, int index){
    if(list == NULL){
        log(ERROR, "linkedList.c", "List is null, cannot add an element", __LINE__);
        return ERR_ADD_NODE;
    }
    
    char debugMsg[64];
    
    if(index > list->size || index < 0){
        sprintf(debugMsg, "Cannot add an element at index : %d. List size = %d", index, list->size);
        log(INFO, "linkedList.c", debugMsg, __LINE__);
        return ERR_ADD_NODE;
    }
    
    sprintf(debugMsg, "Add an element at index : %d. List size = %d", index, list->size);
    log(INFO, "linkedList.c", debugMsg, __LINE__);
    
    struct node* newNode = malloc(sizeof(struct node));
    newNode->element = element;
    
    // Add element to the head 
    if(isEmpty(list) || index == 0){
        log(INFO, "linkedList.c", "Add element to the head of the list", __LINE__);
        newNode->next = list->head;
        newNode->previous = list->tail; 
        
        if(list->head != NULL){
            list->head->previous = newNode;
        }
        
        if(list->tail != NULL){
            list->tail->next = newNode;
        }
        
        list->head = newNode;
        
        if(isEmpty(list)){
            list->tail = newNode;
            newNode->next = list->head;
            newNode->previous = list->tail; 
        }
    } else if(index == list->size) {
        // Add element to the tail 
        log(INFO, "linkedList.c", "Add element to the tail of the list", __LINE__);
        newNode->next = list->head;
        newNode->previous = list->tail; 
        
        if(list->tail != NULL){
            list->tail->next = newNode;
        }
        
        if(list->head != NULL){
            list->head->previous = newNode;
        }
        
        list->tail = newNode;
    } else {
        // Add element to the index, for performance check if we start from the head or tail to find index
        sprintf(debugMsg, "Add an element at index : %d.", index);
        log(INFO, "linkedList.c", debugMsg, __LINE__);
        struct node* nodeToReplace = get(list, index);
        
        if(nodeToReplace == NULL){
            char debugMsg[64];
            sprintf(debugMsg, "Cannot add element at index %d, cannot find element to replace, it is null", index);
            log(ERROR, "linkedList.c", debugMsg, __LINE__);
            return ERR_ADD_NODE;
        }
        
        // Replace nodeToReplace and adjust link
        struct node* previousNode = nodeToReplace->previous;
        
        newNode->previous = previousNode;
        newNode->next = nodeToReplace;
        
        previousNode->next = newNode;
        nodeToReplace->previous = newNode;
    }
    
    list->lastInsertedIndex = index;
    list->lastInserted = newNode;
    list->size++;
    
    sprintf(debugMsg, "Element added at index : %d. List size = %d", index, list->size);
    log(INFO, "linkedList.c", debugMsg, __LINE__);
    
    return SUCCESS;
}

int removeElementAt(struct linkedList_type* list, int index){
    if(list == NULL){
        log(ERROR, "linkedList.c", "List is null, cannot remove an element", __LINE__);
        return ERR_REMOVE_NODE;
    }
    
    if(isEmpty(list)){
        log(ERROR, "linkedList.c", "List is empty, cannot remove an element", __LINE__);
        return ERR_REMOVE_NODE;
    }
    
    char debugMsg[64];
    
    if(index > list->size || index < 0){
        sprintf(debugMsg, "Cannot remove an element at index : %d. List size = %d", index, list->size);
        log(INFO, "linkedList.c", debugMsg, __LINE__);
        return ERR_REMOVE_NODE;
    }
    
    sprintf(debugMsg, "Remove an element at index : %d. List size = %d", index, list->size);
    log(INFO, "linkedList.c", debugMsg, __LINE__);
    
    // Remove element to the head 
    if(index == 0){
        log(INFO, "linkedList.c", "Remove element to the head of the list", __LINE__);
        struct node* nodeToRemove = list->head;
        struct node* nextNode = nodeToRemove->next;
        struct node* previousNode = nodeToRemove->previous;
        
        previousNode->next = nextNode;
        nextNode->previous = previousNode;
    
        list->head = nextNode;
        free(nodeToRemove);
    } else if(index == list->size-1) {
        // Remove element to the tail 
        log(INFO, "linkedList.c", "Remove element to the tail of the list", __LINE__);
        struct node* nodeToRemove = list->tail;
        struct node* nextNode = nodeToRemove->next;
        struct node* previousNode = nodeToRemove->previous;
        
        previousNode->next = nextNode;
        nextNode->previous = previousNode;
        
        list->tail = previousNode;
    }else {
        // Remove element to the index, for performance check if we start from the head or tail to find index
        sprintf(debugMsg, "Remove an element at index : %d.", index);
        log(INFO, "linkedList.c", debugMsg, __LINE__);
        struct node* nodeToRemove = get(list, index);
        
        if(nodeToRemove == NULL){
            char debugMsg[64];
            sprintf(debugMsg, "Cannot add element at index %d, cannot find element to replace, it is null", index);
            log(ERROR, "linkedList.c", debugMsg, __LINE__);
            return ERR_ADD_NODE;
        }
        
        // Replace nodeToReplace and adjust link
        struct node* previousNode = nodeToRemove->previous;
        struct node* nextNode = nodeToRemove->next;
        
        previousNode->next = nextNode;
        nextNode->previous = previousNode;
    }
    
    list->size--;
    sprintf(debugMsg, "Element removed at index : %d. List size = %d", index,list->size);
    log(INFO, "linkedList.c", debugMsg, __LINE__);
    
    return SUCCESS;
}

struct node* get(struct linkedList_type* list, int index){
    if(isEmpty(list)){
        return NULL;
    }
    
    // verify is the index is valid
    if(list->size-1 < index || index < 0){
        char debugMsg[64];
        sprintf(debugMsg, "Cannot get element at index %d, the size is %d", index, list->size);
        log(ERROR, "linkedList.c", debugMsg, __LINE__);
        return NULL;
    }
    
    // Get head
    if(index == 0) {
        return list->head;
    }
    
    // Get Tail
    if(index == list->size-1) {
        return list->tail;
    }
    
    // Get Any node
    struct node* nodeToReturn = NULL;
    if(index <= (list->size / 2)) {
        // Start from head
        nodeToReturn = list->head;
        for(int i=0 ; i<index; i++){
            if(nodeToReturn->next != NULL) {
                nodeToReturn = nodeToReturn->next;
            } else {
                char debugMsg[64];
                sprintf(debugMsg, "Cannot get element at index %d, element at %d is null", index, i);
                log(ERROR, "linkedList.c", debugMsg, __LINE__);
                return NULL;
            }
        }
    } else {
        // Start from tail
        nodeToReturn = list->tail;
        for(int i=list->size-1 ; i>index; i--){
            if(nodeToReturn->previous != NULL) {
                nodeToReturn = nodeToReturn->previous;
            } else {
                char debugMsg[64];
                sprintf(debugMsg, "Cannot get element at index %d, element at %d is null", index, i);
                log(ERROR, "linkedList.c", debugMsg, __LINE__);
                return NULL;
            }
        }
    }
    
    return nodeToReturn;
}

void displayNode(struct linkedList_type* list, int index){
    char debugMsg[64];
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

int isEmpty(struct linkedList_type* list){
    return list->size == 0;
}

int size(struct linkedList_type* list){
    return list->size;
}
