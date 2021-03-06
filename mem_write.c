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

/**
 * Name: MemWriteValidate
 * Description: Verify the parameters for the Write Pattern Command
 * Argurments: char* params - pointer to the string of the command operands
 * Return Value: uint8_t (boolean) - 0: operands are bad, do not execute command, 
 *                                   1: operands are good, execute command
 */
uint8_t MemWriteValidate(char* params);

/**
 * Name: MemWriteExecute
 * Description: Execute the write to memory command
 * Argurments: char* params - pointer to character string of operands
 * Return Value: NA
 *
 */
void MemWriteExecute(char* params);

COMMAND_INTERFACE_STRUCT MemWriteCommandInterface =
{
  "MWRT",
  "Write a 4 byte value to a memory address. Ex: MWRT 0x12345678 42",
  MemWriteValidate,
  MemWriteExecute,
};

extern uint32_t* memBlockPtr;
extern uint32_t memBlockSizeBytes;
uint8_t MemWriteValidate(char* params)
{
  char* valueStringPtr;
  char* startAddressStringPtr;
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

  startAddressStringPtr = strtok(NULL, " ");

  if(startAddressStringPtr == NULL)
  {
	return 0;
  }
  
  if(isValidNum(valueStringPtr) == 0)
  {
    return 0;
  }
  
  if(isValidNum(startAddressStringPtr) == 0)
  {
    return 0;
  }
  
  if(((uint32_t*)convStringToNum(startAddressStringPtr) < memBlockPtr) ||
     ((uint32_t*)convStringToNum(startAddressStringPtr) >= memBlockPtr + memBlockSizeBytes))
  {
    printf("%p has not been allocated for use. Continue anyway?\n('Y' = Yes, Other = No)\n", convStringToNum(startAddressStringPtr));
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

void MemWriteExecute(char* params)
{
  char* valueStringPtr;
  char* startAddressStringPtr;
  
  if(params[0] == ' ')
  {
	params+=1;
  }

  valueStringPtr = strtok(params, " ");
  startAddressStringPtr = strtok(NULL, " ");  

  printf("Writing %d to %p\n", convStringToNum(valueStringPtr), (uint32_t*)convStringToNum(startAddressStringPtr));
  *((uint32_t*)convStringToNum(startAddressStringPtr)) = convStringToNum(valueStringPtr);
}
