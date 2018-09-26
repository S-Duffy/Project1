


#include "command_interface.h"
#include "stdint.h"

uint8_t MemInvValidate(char* params);
uint8_t MemInvExecute(char* params);

COMMAND_INTERFACE_STRUCT MemInvCommandInterface =
{
  "MINV",
  "Frees the block of memory allocated by MALL. Takes no arguments Ex: MFRE",
  MemInvValidate,
  MemInvExecute,
};


uint8_t MemInvValidate(char* params)
{
  return 1;
}

uint8_t MemInvExecute(char* params)
{
  return 1;
}