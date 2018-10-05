/************************************************************************
 *
 * File: smart_mem_inv.c
 * Description: Implementation of the command that inverts the values in
 *              a specified allocated block of memory
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
#include "time.h"

/**
 * Name: SmartMemInvValidate
 * Description: Verify the parameters for the smart invert memory Command
 * Argurments: char* params - pointer to the string of the command operands
 * Return Value: uint8_t (boolean) - 0: operands are bad, do not execute command, 
 *                                   1: operands are good, execute command
 */
uint8_t SmartMemInvValidate(char* params);

/**
 * Name: SmartMemInvExecute
 * Description: Execute the invert memory command
 * Argurments: char* params - pointer to character string of operands
 * Return Value: NA
 *
 */
void SmartMemInvExecute(char* params);

extern uint32_t* memBlockPtr;
extern uint32_t memBlockSizeBytes;

COMMAND_INTERFACE_STRUCT SmartMemInvCommandInterface =
{
  "SINV",
  "Inverts the values in the block of memory allocated by MALL. \
  Takes 2 arguments: size and offset. Ex: SINV 10 0",
  SmartMemInvValidate,
  SmartMemInvExecute,
};


uint8_t SmartMemInvValidate(char* params)
{  
  char* sizeStringPtr;
  char* offsetStringPtr;
  char* test;
  uint8_t hex;
  char paramCopy[30];
  
  if(params == NULL)
  {
    return 0;
  }
  strcpy(paramCopy, params);

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
  
  if((convStringToNum(offsetStringPtr) + convStringToNum(offsetStringPtr) > (memBlockSizeBytes/4)))
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

void SmartMemInvExecute(char* params)
{
  char* sizeStringPtr;
  char* offsetStringPtr;
  
  // if(params[0] == ' ')
  // {
	// params+=1;
  // }

  sizeStringPtr = strtok(params, " ");
  offsetStringPtr = strtok(NULL, " ");
  uint64_t offset = convStringToNum(offsetStringPtr);
  uint64_t size = convStringToNum(sizeStringPtr);
  
  struct timespec startTime;
  clock_gettime(CLOCK_REALTIME, &startTime);
  for(uint32_t i = 0; i < size; i += 1)
  {
	*(memBlockPtr + offset + i) = *(memBlockPtr + offset + i) ^ 0xFFFFFFFF;  // instructions explicitly state "Use XOR"
  }
  
  struct timespec endTime;
  clock_gettime(CLOCK_REALTIME, &endTime);
  printf("Time taken to invert block: %.2f nano seconds\n", (double)(endTime.tv_nsec - startTime.tv_nsec));
}