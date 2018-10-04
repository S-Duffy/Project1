/************************************************************************
 *
 * File: smart_mem_ver_pattern.c
 * Description: Implementation of the command that verifies that the
 *              pseudo-random number sequence has been written to a 
 *              memory block.
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
#include "sys/time.h"
#include "mem_alloc.h"

/**
 * Name: SmartMemVerPatternValidate
 * Description: Verify the parameters for the Verify Pattern Command
 * Argurments: char* params - pointer to the string of the command operands
 * Return Value: uint8_t (boolean) - 0: operands are bad, do not execute command, 
 *                                   1: operands are good, execute command
 */
uint8_t SmartMemVerPatternValidate(char* params);

/**
 * Name: SmartMemVerPatternExecute
 * Description: Execute the verify pattern command
 * Argurments: char* params - pointer to character string of operands
 * Return Value: NA
 *
 */
void SmartMemVerPatternExecute(char* params);


COMMAND_INTERFACE_STRUCT SmartMemVerPatternCommandInterface =
{
  "SVPA",
  "Verifies Pattern matches the memory space designated by offset and size. Ex SVPA 10 42 0",
  SmartMemVerPatternValidate,
  SmartMemVerPatternExecute,
};

uint8_t SmartMemVerPatternValidate(char* params)
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

void SmartMemVerPatternExecute(char* params)
{
  struct timespec startTime;
  clock_gettime(CLOCK_REALTIME, &startTime);
 
  char* sizeStringPtr;
  uint64_t size;
  char* seedStringPtr;
  uint64_t seed;
  char* offsetStringPtr;
  uint64_t offset;
  uint8_t patternsMatch = 1;
  
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
    uint32_t randNum = seed * ((uint64_t) &convStringToNum) ^ 0xAAAAAAAA;
    if(*(memBlockPtr + offset + i) != randNum)
    {
	  patternsMatch = 0;
      printf("Mismatch at offset %d. Expected: %d. Found: %d\n", i, randNum, *(memBlockPtr + offset + i));
    }
  }
  
  if(patternsMatch == 1)
  {
	printf("Pattern Match Successful\n");
    struct timespec endTime;
    clock_gettime(CLOCK_REALTIME, &endTime);
    printf("Time taken to verify pattern: %.2f nano seconds\n", (double)(endTime.tv_nsec - startTime.tv_nsec));
  }	  
}
