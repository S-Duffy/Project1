/************************************************************************
 *
 * File: mem_write_pattern.c
 * Description: Implementation of command that writes pseudo-random numbers
 *              to a designated block of memory
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

/**
 * Name: MemWritePatternValidate
 * Description: Verify the operands of the command
 * Argurments: char* params - character string of command operands
 * Return Value: uint8_t (boolean) 0: operands are invalid
 *                                 1: operands are valid
 */
uint8_t MemWritePatternValidate(char* params);

/**
 * Name: MemWritePatternExecute
 * Description: Executes the write random pattern comman
 * Argurments: char* params - character string of the operand
 * Return Value: NA
 *
 */
void MemWritePatternExecute(char* params);

extern uint32_t* memBlockPtr;
extern uint32_t memBlockSizeBytes;

COMMAND_INTERFACE_STRUCT MemWritePatternCommandInterface =
{
  "MWPA",
  "Write a pattern to a memory block designated by start address and size. Ex: 0x12345678 100",
  MemWritePatternValidate,
  MemWritePatternExecute,
};


uint8_t MemWritePatternValidate(char* params)
{
  char* seedStringPtr;
  char* sizeStringPtr;
  char* startAddressStringPtr;
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
  
  startAddressStringPtr = strtok(NULL, " ");

  if(startAddressStringPtr == NULL)
  {
	return 0;
  }
  

  
  if(isValidNum(seedStringPtr) == 0)
  {
    return 0;
  }
  
  if(isValidNum(startAddressStringPtr) == 0)
  {
    return 0;
  }
 
  if(isValidNum(sizeStringPtr) == 0)
  {
    return 0;
  }
 
  if(((uint32_t*)convStringToNum(startAddressStringPtr) < memBlockPtr) ||
     ((uint32_t*)convStringToNum(startAddressStringPtr) + convStringToNum(sizeStringPtr) > memBlockPtr + (memBlockSizeBytes/4)))
  {
	printf("%p %d %p %d\n", (uint32_t*)convStringToNum(startAddressStringPtr), convStringToNum(sizeStringPtr), memBlockPtr,  (memBlockSizeBytes/4));
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

void MemWritePatternExecute(char* params)
{
  char* sizeStringPtr;
  uint64_t size;
  char* seedStringPtr;
  uint64_t seed;
  char* startAddressStringPtr;
  uint32_t* startAddress;
  
  if(params[0] == ' ')
  {
	params+=1;
  }

  seedStringPtr = strtok(params, " ");
  sizeStringPtr = strtok(NULL, " ");
  startAddressStringPtr  = strtok(NULL, " ");

  startAddress = (uint32_t*) convStringToNum(startAddressStringPtr);
  size = convStringToNum(sizeStringPtr);
  seed = convStringToNum(seedStringPtr);
  
   
  for(uint32_t i = 0; i < size; i += 1)
  {
    seed = seed * 37;
    *(startAddress + i) = seed * ((uint64_t) &convStringToNum) ^ 0xAAAAAAAAAAAAAAAA;
  }
}