
#include "command_interface.h"
#include "stdint.h"

uint8_t MemVerPatternValidate(char* params);
uint8_t MemVerPatternExecute(char* params);

COMMAND_INTERFACE_STRUCT MemVerPatternCommandInterface =
{
  "MVPA",
  "Verifies Pattern matches the memory space designated by address and size. Ex MVPA 0x12345678 100",
  MemVerPatternValidate,
  MemVerPatternExecute,
};


uint8_t MemVerPatternValidate(char* params)
{
  return 1;
}

uint8_t MemVerPatternExecute(char* params)
{
  return 1;
}