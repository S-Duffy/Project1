


#include "command_interface.h"
#include "stdint.h"

uint8_t MemDisplayValidate(char* params);
uint8_t MemDisplayExecute(char* params);

COMMAND_INTERFACE_STRUCT MemDisplayCommandInterface =
{
  "MDIS",
  "Displays a block of memory. Takes 2 arguments: Starting Address and Size (in 4 byte words). Ex: MDIS 0x12345678 100",
  MemDisplayValidate,
  MemDisplayExecute,
};


uint8_t MemDisplayValidate(char* params)
{
  return 1;
}

uint8_t MemDisplayExecute(char* params)
{
  return 1;
}