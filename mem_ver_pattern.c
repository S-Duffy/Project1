/************************************************************************
 *
 * File: mem_ver_pattern.c
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
#include "time.h"

/**
 * Name: MemVerPatternValidate
 * Description: Verify the parameters for the Verify Pattern Command
 * Argurments: char* params - pointer to the string of the command operands
 * Return Value: uint8_t (boolean) - 0: operands are bad, do not execute command, 
 *                                   1: operands are good, execute command
 */
uint8_t MemVerPatternValidate(char* params);

/**
 * Name: MemVerPatternExecute
 * Description: Execute the verify pattern command
 * Argurments: char* params - pointer to character string of operands
 * Return Value: NA
 *
 */
void MemVerPatternExecute(char* params);

extern uint32_t* memBlockPtr;
extern uint32_t memBlockSizeBytes;

COMMAND_INTERFACE_STRUCT MemVerPatternCommandInterface =
{
  "MVPA",
  "Verifies Pattern matches the memory space designated by address and size. Ex MVPA 0x12345678 100",
  MemVerPatternValidate,
  MemVerPatternExecute,
};

uint8_t MemVerPatternValidate(char* params)
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
     ((uint32_t*)convStringToNum(startAddressStringPtr) + convStringToNum(sizeStringPtr) >= memBlockPtr + memBlockSizeBytes))
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

void MemVerPatternExecute(char* params)
{
  clock_t startTime = clock();
  struct timespec now;
  clock_gettime(CLOCK_REALTIME, &now);
  struct itimerspec plz;
  timer_gettime(CLOCK_REALTIME, &plz);
  time(&startTime);
  
  printf("%f\n", clock());
  printf("%f\n", now);
  printf("%f\n", startTime);
  printf("%f\n", plz);
  
  char* sizeStringPtr;
  uint64_t size;
  char* seedStringPtr;
  uint64_t seed;
  char* startAddressStringPtr;
  uint32_t* startAddress;
  uint8_t patternsMatch = 1;
  
   
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
    uint32_t randNum = seed * ((uint64_t) &convStringToNum) ^ 0xAAAAAAAA;
    if(*(startAddress + i) != randNum)
    {
	  patternsMatch = 0;
      printf("Mismatch at %p. Expected: %p. Found: %p\n", startAddress + i, randNum, *(startAddress + i));
    }
  }
  
  if(patternsMatch == 1)
  {
	clock_t endTime;
	time(&endTime);
    struct timespec then;
    clock_gettime(CLOCK_REALTIME, &then);
    clock_t then2 = clock();
	printf("then: %f\n", then);
	printf("now: %f\n", now);
	printf("then2: %f\n", then);
	printf("now: %f\n", now);	
    printf("Time taken to verify pattern: %f seconds\n", difftime(endTime,startTime));
  }	  
}

