

#include "command_interface.h"
#include "stdint.h"

uint8_t MemWritePatternValidate(char* params);
uint8_t MemWritePatternExecute(char* params);

COMMAND_INTERFACE_STRUCT MemWritePatternCommandInterface =
{
  "MWPA",
  "Write a pattern to a memory block designated by start address and size. Ex: 0x12345678 100",
  MemWritePatternValidate,
  MemWritePatternExecute,
};


uint8_t MemWritePatternValidate(char* params)
{
  return 1;
}

uint8_t MemWritePatternExecute(char* params)
{
  return 1;
}