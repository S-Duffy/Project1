/************************************************************************
 *
 * File: mem_display.c
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

/**
 * Name: MemDisplayValidate
 * Description: Validates the operands of the display memory command
 * Argurments: char* params - character string of operands
 * Return Value: uint8_t (boolean) 0: operands are invalid
 *                                 1: operands are valid
 */
uint8_t MemDisplayValidate(char* params);

/**
 * Name: MemFreeExecute
 * Description: Executes the display memory command
 * Argurments: char* params - character string of the operands
 * Return Value: NA
 *
 */
void MemDisplayExecute(char* params);

COMMAND_INTERFACE_STRUCT MemDisplayCommandInterface =
{
  "MDIS",
  "Displays a block of memory. Takes 2 arguments: Starting Address and Size (in 4 byte words). Ex: MDIS 100 0x12345678",
  MemDisplayValidate,
  MemDisplayExecute,
};

extern uint32_t* memBlockPtr;
extern uint32_t memBlockSizeBytes;
uint8_t MemDisplayValidate(char* params)
{
  char* sizeStringPtr;
  char* validateStartAddressStringPtr;
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

  validateStartAddressStringPtr = strtok(NULL, " ");

  if(validateStartAddressStringPtr == NULL)
  {
	return 0;
  }
  
  if(isValidNum(sizeStringPtr) == 0)
  {
    return 0;
  }
  
  if(isValidNum(validateStartAddressStringPtr) == 0)
  {
    return 0;
  }
  
  if(((uint32_t*)convStringToNum(validateStartAddressStringPtr) < memBlockPtr) ||
     ((uint32_t*)convStringToNum(validateStartAddressStringPtr) >= memBlockPtr + (memBlockSizeBytes/4)))
  {
    printf("%p has not been allocated for use. Continue anyway?\n('Y' = Yes, Other = No)\n", convStringToNum(validateStartAddressStringPtr));
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

void MemDisplayExecute(char* params)
{
  char* sizeStringPtr;
  char* startAddressStringPtr;

  if(params[0] == ' ')
  {
	params+=1;
  }
  // printf("params: %s\n", params);
  sizeStringPtr = strtok(params, " ");
  startAddressStringPtr = strtok(NULL, " ");
  
  uint32_t* startingAddress = (uint32_t*) convStringToNum(startAddressStringPtr);
  
  uint64_t size = convStringToNum(sizeStringPtr);
  printf("Reading %d words starting at address %p\n", size, startingAddress);
    
  for(uint32_t i = 0; i < size; i += 1)
  {
    printf("%p : %d\n", startingAddress + i, *(startingAddress + i));
  }
}