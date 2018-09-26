



#include "command_interface.h"
#include "stdint.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"

uint8_t MemAllocValidate(char* params);
uint8_t MemAllocExecute(char* params);

uint32_t* memBlockPtr = NULL;

uint16_t placeValues[] = {
	1, 10, 100, 1000, 10000,
};

COMMAND_INTERFACE_STRUCT MemAllocCommandInterface =
{
  "MALL",
  "Allocates a block of memory. Takes 1 argument to determine size. Ex: MALL 100",
  MemAllocValidate,
  MemAllocExecute,
};

uint32_t convStringToNum(char* numberString)
{
  uint32_t integer = 0;
  
  for(uint8_t i = 0; i <strlen(numberString) -1; i+= 1)
  {
	// printf("\nDIGIT: %d", (numberString[i] - '0'));
	// printf("\nPV: %d", placeValues[strlen(numberString) - i - 2]);
    integer += (numberString[i] - '0') * placeValues[strlen(numberString) - i - 2];
    // printf("\ninteger: %d", integer);
  }
  
  return integer;
	
}

uint8_t MemAllocValidate(char* params)
{
  return 1;
}

uint8_t MemAllocExecute(char* params)
{
  uint16_t sizeInWords = convStringToNum(params + 1);

  memBlockPtr = malloc(sizeInWords * 4);
  return 1;
}