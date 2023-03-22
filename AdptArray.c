/* 
    This "AdptArray.c" file is part of the ADT assignment.

    In the AdptArray.c file We define the structure of the array,
    and in addition all the functions required to manage it.

    In order to create the current file I took help from:
        a. My solution to the test that was in systems programming A. 
        b. The solution published on the course website
 
    Of course I wrote all the code by myself. 

    Daniel Nissan Schneiderman

    20.03.2023  

*/
 
#include <string.h>
#include <stdlib.h>
#include "AdptArray.h"


// The adptive array struct 
typedef struct AdptArray_
{
	int ArrSize;   
	PElement* pElemArr;
	DEL_FUNC delFunc;  
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc; 
}AdptArray;




/// @brief  CreateAdptArray() creates a new addaptive array that holds element from a given type.
///    It can hold any type of element that the user wants.
///    every array can hold only 1 type. 
///    The user needs tp provide 3 functions: 
///    cp_func - the function that 
///    del_func - the function that 
///    print_fuc - the function that 
/// @param cp_func the copy function - copies an element from the array type
/// @param del_func the delete function - deletes an element from the array type
/// @param print_func the print function - prints an element of the array type 
/// @return the new array 
PAdptArray CreateAdptArray(COPY_FUNC cp_func, DEL_FUNC del_func,PRINT_FUNC print_func){
   
    // allocate memory for new array 
    PAdptArray newArr = (PAdptArray)malloc(sizeof(AdptArray));

    // check for allocating error
    if(newArr == NULL){
        return NULL;
    }
    // Initialize the array properties 
    newArr->ArrSize = 0; 
    newArr->pElemArr = NULL; 
    newArr->delFunc = del_func; 
    newArr->copyFunc = cp_func;
    newArr->printFunc =  print_func; 

    return newArr;
}

/// @brief The function delete the given addaptive array 
/// @param pAdpArr the addaptive array to delete
void DeleteAdptArray(PAdptArray pAdpArr){

    // check the array is not null 
    if(pAdpArr == NULL){
        return; 
    }

    // go over the pElemArr and if the element in the current index isn't null - delete it
    for(int i=0; i<pAdpArr->ArrSize; i++){
        if((pAdpArr->pElemArr)[i] != NULL){
            pAdpArr->delFunc((pAdpArr->pElemArr)[i]);
        }
    }
    // free the pElemArr and pAdpArr
    free(pAdpArr->pElemArr);
    free(pAdpArr); 
}

/// @brief the function sets a new given element to the pElemArr in a given index
/// @param pAdpArr the appdive array 
/// @param index the index to insert to 
/// @param pNewElement the new elemnt to insert 
/// @return SUCCESS when succeeded to set the element and FAIL when failed 
Result SetAdptArrayAt(PAdptArray pAdpArr, int index, PElement pNewElement){

    // Check for unvalid input 
    if(pAdpArr == NULL || index<=0 || pNewElement == NULL){
        return FAIL; 
    }

    // if given index is bigger than current array size - 
    // allocate more space for the new pElemArr 
    if(index >= pAdpArr->ArrSize){
        
        PElement* newpElement = (PElement*)calloc(index + 1, sizeof(PElement));
       
        // check for allocating error
        if (newpElement == NULL) {
            return FAIL;
        }

        // copy the old pElemeArr to the new one. 
        memcpy(newpElement, pAdpArr->pElemArr, (pAdpArr->ArrSize) * sizeof(PElement));
       
        // free the memory of the old one, and insert the new one 
        free(pAdpArr->pElemArr);
        pAdpArr->pElemArr = newpElement; 

       
    }
    // if the old element in the given index is not null - delete the element 
    if ((pAdpArr->pElemArr)[index] != NULL) {
        pAdpArr->delFunc((pAdpArr->pElemArr)[index]);
    }

    // copy the new given element into the given index 
    (pAdpArr->pElemArr)[index] = pAdpArr->copyFunc(pNewElement); 

    // if we changed the size of the element array - update array size. 
    if(index >= pAdpArr->ArrSize){
        pAdpArr->ArrSize = index + 1;
    }

    return SUCCESS; 

}


/// @brief the function returns an element in a given array 
/// @param pAdpArr the array
/// @param index the index 
/// @return the element 
PElement GetAdptArrayAt(PAdptArray pAdpArr, int index){
    
    // check for unvalid input  
    if ( index<0 || index>(pAdpArr->ArrSize) || (pAdpArr->pElemArr)[index] == NULL) {
        return NULL;
    }
    
    return pAdpArr->copyFunc((pAdpArr->pElemArr)[index]); 
}


/// @brief  the function return the array size. if array is null return -1 
/// @param pAdpArr the given array 
/// @return the size of array 
int GetAdptArraySize(PAdptArray pAdpArr){
    if(pAdpArr == NULL)
    {
        return -1; 
    }
    
    return pAdpArr->ArrSize;
}


/// @brief PrintDB print the element in the array using the print function 
/// @param pAdpArr the given array 
void PrintDB(PAdptArray pAdpArr){

    if (pAdpArr == NULL) {
        return;
    }

    // loop over the element in the array and if the array in the current index isn't null
    // print it. 
    for(int i=0; i<pAdpArr->ArrSize; i++){
        if( pAdpArr->pElemArr[i] != NULL){
            pAdpArr->printFunc(pAdpArr->pElemArr[i]);
        }
    }
}