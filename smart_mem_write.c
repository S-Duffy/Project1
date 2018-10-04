/************************************************************************
 *
 * File: 
 * Description:
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
 * Name: SmartWriteValidate
 * Description: Verify the parameters for the Smart Write to Memory Command
 * Argurments: char* params - pointer to the string of the command operands
 * Return Value: uint8_t (boolean) - 0: operands are bad, do not execute command, 
 *                                   1: operands are good, execute command
 */
uint8_t SmartWriteValidate(char* params);

/**
 * Name: SmartWriteExecute
 * Description: Execute the smart write to memory command
 * Argurments: char* params - pointer to character string of operands
 * Return Value: NA
 *
 */
void SmartWriteExecute(char* params);

COMMAND_INTERFACE_STRUCT SmartWriteCommandInterface =
{
  "SWRT",
  "Write a 4 byte value to a memory offset from the base of the allocated block. Ex: SWRT 42 1",
  SmartWriteValidate,
  SmartWriteExecute,
};

uint8_t SmartWriteValidate(char* params)
{
  char* valueStringPtr;
  char* addressOffsetStringPtr;
  char paramCopy[30];
  uint8_t hex;
  
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
  
  valueStringPtr = strtok(paramCopy, " ");
  
  if(valueStringPtr == NULL)
  {
    return 0;
  }

  addressOffsetStringPtr = strtok(NULL, " ");

  if(addressOffsetStringPtr == NULL)
  {
	return 0;
  }
  
  if(isValidNum(valueStringPtr) == 0)
  {
    return 0;
  }
  
  if(isValidNum(addressOffsetStringPtr) == 0)
  {
    return 0;
  }
  
  if(((uint64_t)convStringToNum(addressOffsetStringPtr) < 0) ||
     ((uint64_t)convStringToNum(addressOffsetStringPtr) >= (memBlockSizeBytes/4)))
  {
    printf("This address has not been allocated for use. Continue anyway?\n('Y' = Yes, Other = No)\n");
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

void SmartWriteExecute(char* params)
{
  char* valueStringPtr;
  char* offsetStringPtr;
  
  if(params[0] == ' ')
  {
	params+=1;
  }

  valueStringPtr = strtok(params, " ");
  offsetStringPtr = strtok(NULL, " ");  

  printf("Writing %d to %p + %d\n", convStringToNum(valueStringPtr), memBlockPtr, (uint32_t*)convStringToNum(offsetStringPtr));
  *(memBlockPtr + (uint64_t)convStringToNum(offsetStringPtr)) = convStringToNum(valueStringPtr);
}
