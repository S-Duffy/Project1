
#include "command_interface.h"
#include "stdint.h"


uint8_t MemWriteValidate(char* params);
uint8_t MemWritenExecute(char* params);

COMMAND_INTERFACE_STRUCT MemWriteCommandInterface =
{
  "MWRT",
  "Write a 4 byte value to a memory address. Ex: MWRT 0x12345678 42",
  MemWriteValidate,
  MemWritenExecute,
};


uint8_t MemWriteValidate(char* params)
{
  return 1;
}

uint8_t MemWritenExecute(char* params)
{
  return 1;
}
