/************************************************************************
 *
 * File: mem_alloc.c
 * Description: Implementation of the allocate memory command
 * 
 * Author: Sean Duffy
 * Tools: gcc
 * Leveraged Code: See "#include"s
 * Links: NA
 *
***********************************************************************/



#include "command_interface.h"
#include "stdint.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"

/**
 * Name: MemAllocValidate
 * Description: Verify the parameters for the allocate memory Command
 * Argurments: char* params - pointer to the string of the command operands
 * Return Value: uint8_t (boolean) - 0: operands are bad, do not execute command, 
 *                                   1: operands are good, execute command
 */
uint8_t MemAllocValidate(char* params);

/**
 * Name: MemAllocExecute
 * Description: Execute the allocat memory command
 * Argurments: char* params - pointer to character string of operands
 * Return Value: NA
 *
 */
void MemAllocExecute(char* params);

uint32_t* memBlockPtr = NULL;
uint32_t memBlockSizeBytes = 0;

COMMAND_INTERFACE_STRUCT MemAllocCommandInterface =
{
  "MALL",
  "Allocates a block of memory. Takes 1 argument to determine size. Ex: MALL 100",
  MemAllocValidate,
  MemAllocExecute,
};

extern uint32_t* memBlockPtr;
extern uint32_t memBlockSizeBytes;
uint8_t MemAllocValidate(char* params)
{
  char* sizeInWordsPtr;
  char paramCopy[30];
  
  if(params == NULL)
  {
    return 0;
  }
  
  if(strlen(params) > 30)
  {
    return 0;
  }

  strcpy(paramCopy, params);
  
  sizeInWordsPtr = strtok(paramCopy, " ");
  
  if(sizeInWordsPtr == NULL)
  {
    return 0;
  }
  if(isValidNum(sizeInWordsPtr) == 0)
  {
	return 0;
  }
  return 1;
}

void MemAllocExecute(char* params)
{
  char* sizeInWordsPtr = strtok(params, " ");
  uint64_requestedSizeInWords = convStringToNum(sizeInWordsPtr);
  uint16_t sizeInWords = convStringToNum(sizeInWordsPtr);

  if(sizeInWords <uint64_requestedSizeInWords)
  {
     printf("Sorry, max supported size is 65535 words\n");   
  }
  
  memBlockPtr = malloc(sizeInWords * 4);
  memBlockSizeBytes = sizeInWords * 4;
  if(memBlockPtr != NULL)
  {
    printf("Your new %d word block of memory starts at address: %p\n", sizeInWords, memBlockPtr);
  }
  else
  {
    printf("Sorry, a memory block of that size was not available, try a smaller size\n");    
  }
}