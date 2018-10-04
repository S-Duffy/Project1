/************************************************************************
 *
 * File: smart_mem_display.c
 * Description: Implementation of command that prints blocks of memory via stdio
 * 
 * Author: Sean Duffy
 * Tools: gcc
 * Leveraged Code: See "#include"s
 * Links: NA
 *
***********************************************************************/

#include "command_interface.h"
#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "mem_alloc.h"

/**
 * Name: SmartMemDisplayValidate
 * Description: Validates the operands of the smart display memory command
 * Argurments: char* params - character string of operands
 * Return Value: uint8_t (boolean) 0: operands are invalid
 *                                 1: operands are valid
 */
uint8_t SmartMemDisplayValidate(char* params);

/**
 * Name: SmartMemDisplayExecute
 * Description: Executes the display memory command
 * Argurments: char* params - character string of the operands
 * Return Value: NA
 *
 */
void SmartMemDisplayExecute(char* params);

COMMAND_INTERFACE_STRUCT SmartMemDisplayCommandInterface =
{
  "SDIS",
  "Displays a block of memory. Takes 2 arguments: Starting offset and Size (in 4 byte words). Ex: SDIS 100 0",
  SmartMemDisplayValidate,
  SmartMemDisplayExecute,
};

extern uint32_t* memBlockPtr;
extern uint32_t memBlockSizeBytes;
uint8_t SmartMemDisplayValidate(char* params)
{
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
  // printf("paramCopy: %s\n", paramCopy);
  
  sizeStringPtr = strtok(paramCopy, " ");
  
  if(sizeStringPtr == NULL)
  {
    return 0;
  }

  offsetStringPtr = strtok(NULL, " ");

  if(offsetStringPtr == NULL)
  {
	return 0;
  }
  
  if(isValidNum(sizeStringPtr) == 0)
  {
    return 0;
  }
  
  if(isValidNum(offsetStringPtr) == 0)
  {
    return 0;
  }
  
  if((convStringToNum(offsetStringPtr) +convStringToNum(offsetStringPtr) > (memBlockSizeBytes/4)))
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

void SmartMemDisplayExecute(char* params)
{
  char* sizeStringPtr;
  char* offsetStringPtr;

  if(params[0] == ' ')
  {
	params+=1;
  }
  // printf("params: %s\n", params);
  sizeStringPtr = strtok(params, " ");
  offsetStringPtr = strtok(NULL, " ");
  
  uint64_t offset = convStringToNum(offsetStringPtr);
  
  uint64_t size = convStringToNum(sizeStringPtr);
  printf("Reading %d words starting at offset %d from start of allocated block.\n", size, offset);
    
  for(uint32_t i = 0; i < size; i += 1)
  {
    printf("%d : %d\n", offset + i, *(memBlockPtr + offset + i));
  }
}
