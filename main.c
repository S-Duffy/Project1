// Main.c
// Should receive commands and direct them to appropriate module
//
//
//

#include "stdio.h"
#include "string.h"
#include "stdint.h"

#include "command_interface.h"
#include "help.h"
#include "mem_alloc.h"
#include "mem_free.h"
#include "mem_display.h"
#include "mem_write.h"
#include "mem_inv.h"
#include "mem_write_pattern.h"
#include "mem_ver_pattern.h"

char currentCommandString[30];
char* currentCommandStringPtr;
char currentOpcodeString[15];

COMMAND_INTERFACE_STRUCT* commandInterfaces[] =
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

int main(void)
{
  // Display greeting message with help function explanation
  printf("Entering Hardware Evaluation Mode.\n");
  printf("Type 'HELP' for command descriptions.\n");
  printf("Type 'QUIT' to exit Hardware Evaluation Mode.\n");
  while(1)
  {
    // Retrieve Input
    gets(currentCommandString);
	
	currentCommandStringPtr = strcat((void*)currentCommandString, " ");
	
    if(strcmp(currentCommandString, "QUIT ") == 0)
    {
      break;
    }
	 // printf("Read: %s\n", currentCommandString);
    // Identify Callback
	
	// printf("%d\n", strchr(currentCommandString, ' ') - currentCommandString);
	strncpy((char*)&currentOpcodeString, (char*)&currentCommandString, (strchr(currentCommandString, ' ') - currentCommandString));
	// printf("Opcode: %s\n", currentOpcodeString);
	
	uint8_t i = 0;
	while((commandInterfaces[i] != NULL) && 
	       (strcmp(currentOpcodeString, commandInterfaces[i]->commandString) != 0))
	{
	  i += 1;
	}
	// printf("Matches: %s\n", commandInterfaces[i]->commandString);
	if(commandInterfaces[i] == NULL)
	{
		  printf("Invalid Command: '%s'\n", currentCommandString);
	}
    // Verify Parameters
	else
	{
	  // printf("Validating: %s\n", strchr(currentCommandString, ' '));
	  if(commandInterfaces[i]->validate(strchr(currentCommandString, ' ')))
	  {
		// printf("Validated\n");
		commandInterfaces[i]->execute(strchr(currentCommandString, ' '));
	  }
	  else
	  {
		printf("Invalid Parameters: %s.\n", currentCommandString);
	  }
		  
	}
    // Perform Operation
  }

  printf("Exiting Hardware Evaluation Mode.\n");

  return 0;

}
