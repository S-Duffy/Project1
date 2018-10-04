/************************************************************************
 *
 * File: help.c
 * Description: Implementation of the help command
 * 
 * Author: Sean Duffy
 * Tools: gcc
 * Leveraged Code: See "#include"s
 * Links: NA
 *
***********************************************************************/

#include "string.h"
#include "command_interface.h"
#include "stdio.h"
#include "stdint.h"

#include "mem_alloc.h"
#include "mem_free.h"
#include "mem_display.h"
#include "mem_write.h"
#include "mem_inv.h"
#include "mem_write_pattern.h"
#include "mem_ver_pattern.h"
#include "smart_mem_display.h"
#include "smart_mem_write.h"
#include "smart_mem_inv.h"
#include "smart_mem_write_pattern.h"
#include "smart_mem_ver_pattern.h"

/**
 * Name: HelpValidate
 * Description: Verify the parameters for the help Command
 * Argurments: char* params - pointer to the string of the command operands
 * Return Value: uint8_t (boolean) - 0: operands are bad, do not execute command, 
 *                                   1: operands are good, execute command
 */
uint8_t HelpValidate(char* params);

/**
 * Name: HelpExecute
 * Description: Execute the help command
 * Argurments: char* params - pointer to character string of operands
 * Return Value: NA
 *
 */
void HelpExecute(char* params);

COMMAND_INTERFACE_STRUCT HelpCommandInterface =
{
	"HELP",
	"You're doing it right",
	HelpValidate,
	HelpExecute,
};

COMMAND_INTERFACE_STRUCT* commandInterfacesForHelp[] =
{
  &HelpCommandInterface,
  &MemAllocCommandInterface,
  &MemDisplayCommandInterface,
  &MemFreeCommandInterface,
  &MemInvCommandInterface,
  &MemVerPatternCommandInterface,
  &MemWriteCommandInterface,
  &MemWritePatternCommandInterface,
  &SmartWriteCommandInterface,
  &SmartMemWritePatternCommandInterface,  
  &SmartMemInvCommandInterface,
  &SmartMemVerPatternCommandInterface,  
  &SmartMemDisplayCommandInterface,  
  NULL,
};

uint8_t HelpValidate(char* params)
{	
  return 1;
}

void HelpExecute(char* params)
{
  uint8_t i = 0;

  printf("Supported Commands are:\n");
  // loop through supported command
  while(commandInterfacesForHelp[i] != NULL)
  {
    if(commandInterfacesForHelp[i] -> commandHelpString != NULL)
    {
      printf("%s: %s\n", commandInterfacesForHelp[i] -> commandString, commandInterfacesForHelp[i] -> commandHelpString);
    }
    i += 1;
  }
}
