


#include "command_interface.h"
#include "mem_alloc.h"
#include "stdint.h"
#include <stdlib.h>

uint8_t MemFreeValidate(char* params);
uint8_t MemFreeExecute(char* params);

COMMAND_INTERFACE_STRUCT MemFreeCommandInterface =
{
  "MFRE",
  "Frees the block of memory allocated by MALL. Takes no arguments Ex: MFRE",
  MemFreeValidate,
  MemFreeExecute,
};


uint8_t MemFreeValidate(char* params)
{
  return 1;
}

uint8_t MemFreeExecute(char* params)
{
  free(memBlockPtr);
  return 1;
}