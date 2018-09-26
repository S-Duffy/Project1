// help.c
// Implements the help function
//
//
//
//

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

int HelpValidate(char* params);
int HelpExecute(char* params);

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
  NULL,
};

int HelpValidate(char* params)
{	
  return 1;
}

int HelpExecute(char* params)
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
