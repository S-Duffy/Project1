/************************************************************************
 *
 * File: mem_free.c
 * Description: Implementation of the command that de-allocates a memory block
 * 
 * Author: Sean Duffy
 * Tools: gcc
 * Leveraged Code: See "#include"s
 * Links: NA
 *
***********************************************************************/
#include "command_interface.h"
#include "mem_alloc.h"
#include "stdint.h"
#include <stdlib.h>

/**
 * Name: MemFreeValidate
 * Description: Validates the operands of the free memory command
 * Argurments: char* params - character string of operand
 * Return Value: uint8_t (boolean) 0: operands are invalid
 *                                 1: operands are valid
 */
uint8_t MemFreeValidate(char* params);

/**
 * Name: MemFreeExecute
 * Description: Executes the free memory command
 * Argurments: char* params - character string of the operand
 * Return Value: NA
 *
 */
void MemFreeExecute(char* params);

COMMAND_INTERFACE_STRUCT MemFreeCommandInterface =
{
  "MFRE",
  "Frees the block of memory allocated by MALL. Takes no arguments Ex: MFRE",
  MemFreeValidate,
  MemFreeExecute,
};


uint8_t MemFreeValidate(char* params)
{

  if(params == NULL)
  {
    return 1;
  }
  
  return 0;
}

void MemFreeExecute(char* params)
{
  free(memBlockPtr);
}