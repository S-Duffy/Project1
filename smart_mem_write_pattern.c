/************************************************************************
 *
 * File: smart_mem_write_pattern.c
 * Description: Implementation of command that writes pseudo-random numbers
 *              to a designated allocated block of memory
 * 
 * Author: Sean Duffy
 * Tools: gcc
 * Leveraged Code: See "#include"s
 * Links: NA
 *
***********************************************************************/

#include "command_interface.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "mem_alloc.h"

/**
 * Name: SmartMemWritePatternValidate
 * Description: Verify the operands of the Smart write pattern to memory command
 * Argurments: char* params - character string of command operands
 * Return Value: uint8_t (boolean) 0: operands are invalid
 *                                 1: operands are valid
 */
uint8_t SmartMemWritePatternValidate(char* params);

/**
 * Name: SmartMemWritePatternExecute
 * Description: Executes the smart write random pattern comman
 * Argurments: char* params - character string of the operand
 * Return Value: NA
 *
 */
void SmartMemWritePatternExecute(char* params);

COMMAND_INTERFACE_STRUCT SmartMemWritePatternCommandInterface =
{
  "SWPA",
  "Write a pattern to the allocated memory block by designating size, seed, and offset . Ex: SWPA 10 42 0",
  SmartMemWritePatternValidate,
  SmartMemWritePatternExecute,
};


uint8_t SmartMemWritePatternValidate(char* params)
{
  char* seedStringPtr;
  char* sizeStringPtr;
  char* offsetStringPtr;
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
  
  seedStringPtr = strtok(paramCopy, " ");
  
  if(seedStringPtr == NULL)
  {
    return 0;
  }

  sizeStringPtr = strtok(NULL, " ");
  
  if(sizeStringPtr == NULL)
  {
	return 0;
  }  
  
  offsetStringPtr = strtok(NULL, " ");

  if(offsetStringPtr == NULL)
  {
	return 0;
  }
  

  
  if(isValidNum(seedStringPtr) == 0)
  {
    return 0;
  }
  
  if(isValidNum(offsetStringPtr) == 0)
  {
    return 0;
  }
 
  if(isValidNum(sizeStringPtr) == 0)
  {
    return 0;
  }

  if((convStringToNum(sizeStringPtr) + convStringToNum(offsetStringPtr) > (memBlockSizeBytes/4)))
  {
    printf("At least part of this block has not been allocated for use. Continue anyway?\n('Y' = Yes, Other = No)\n");
	char* response;
	char* unused = gets(response);
	printf(response); // echo
	if(strcmp(response, "Y") == 0)
	{
      return 1;
	}
	else
	{
      return 0;
	}
  }
  return 1;
}

void SmartMemWritePatternExecute(char* params)
{
  char* sizeStringPtr;
  uint64_t size;
  char* seedStringPtr;
  uint64_t seed;
  char* offsetStringPtr;
  uint32_t offset;
  
  if(params[0] == ' ')
  {
	params+=1;
  }

  seedStringPtr = strtok(params, " ");
  sizeStringPtr = strtok(NULL, " ");
  offsetStringPtr  = strtok(NULL, " ");

  offset = convStringToNum(offsetStringPtr);
  size = convStringToNum(sizeStringPtr);
  seed = convStringToNum(seedStringPtr);
  
   
  for(uint32_t i = 0; i < size; i += 1)
  {
    seed = seed * 37;
    *(memBlockPtr + offset + i) = seed * ((uint64_t) &convStringToNum) ^ 0xAAAAAAAAAAAAAAAA;
  }
}