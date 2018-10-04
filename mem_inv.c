/************************************************************************
 *
 * File: mem_inv.c
 * Description: Implementation of the command that inverts the values in
 *              a specified block of memory
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
 * Name: MemInvValidate
 * Description: Verify the parameters for the invert memory Command
 * Argurments: char* params - pointer to the string of the command operands
 * Return Value: uint8_t (boolean) - 0: operands are bad, do not execute command, 
 *                                   1: operands are good, execute command
 */
uint8_t MemInvValidate(char* params);

/**
 * Name: MemInvExecute
 * Description: Execute the invert memory command
 * Argurments: char* params - pointer to character string of operands
 * Return Value: NA
 *
 */
void MemInvExecute(char* params);

extern uint32_t* memBlockPtr;
extern uint32_t memBlockSizeBytes;

COMMAND_INTERFACE_STRUCT MemInvCommandInterface =
{
  "MINV",
  "Inverts the values in the block of memory allocated by MALL. Takes 2 arguments: \
  size and start address. Ex: MINV 10 0x12345678",
  MemInvValidate,
  MemInvExecute,
};


uint8_t MemInvValidate(char* params)
{  
  char* sizeStringPtr;
  char* startAddressStringPtr;
  char* test;
  uint8_t hex;
  
  if(params == NULL)
  {
    return 0;
  }
  
  sizeStringPtr = strtok(params, " ");
  
  if(sizeStringPtr == NULL)
  {
    return 0;
  }

  startAddressStringPtr = strtok(NULL, " ");

  if(startAddressStringPtr == NULL)
  {
	return 0;
  }
  
  if(isValidNum(sizeStringPtr) == 0)
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
    printf("%p has not been allocated for use. Continue anyway?\n('Y' = Yes, Other = No)\n", startAddressStringPtr);
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

void MemInvExecute(char* params)
{
  char* sizeStringPtr;
  char* startAddressStringPtr;
  
  if(params[0] == ' ')
  {
	params+=1;
  }

  sizeStringPtr = strtok(params, " ");
  startAddressStringPtr = strtok(NULL, " ");
  uint32_t* startingAddress = (uint32_t*) convStringToNum(startAddressStringPtr);
  uint64_t size = convStringToNum(sizeStringPtr);
  printf("Reading %d words starting at address %p\n", size, startingAddress);
  
  
  for(uint32_t i = 0; i < size; i += 1)
  {
    printf("%p : %d\n", startingAddress + i, *(startingAddress + i));
	*(startingAddress + i) = *(startingAddress + i) ^ 0xFFFFFFFFFFFFFFFF;  // instructions explicitly state "Use XOR"
  }
}