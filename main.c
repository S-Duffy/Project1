/************************************************************************
 *
 * File: main.c
 * Description: Main file for the Project 1 project. Primarily relays
 *              messages between the user (usu. stdio) and the files that
 *             implement the supported commands.
 * 
 * Author: Sean Duffy
 * Tools: gcc
 * Leveraged Code: See "#include"s
 * Links: NA
 *
***********************************************************************/

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
#include "smart_mem_write.h"
#include "smart_mem_display.h"
#include "smart_mem_inv.h"
#include "smart_mem_write_pattern.h"
#include "smart_mem_ver_pattern.h"

char currentCommandString[70];
char* currentCommandStringPtr;
char currentOpcodeString[50];
char currentOperands[50];
char* currentOperandsPtr;

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
  &SmartWriteCommandInterface,
  &SmartMemWritePatternCommandInterface,  
  &SmartMemInvCommandInterface,
  &SmartMemVerPatternCommandInterface,  
  &SmartMemDisplayCommandInterface,  
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
    char* unused = gets(currentCommandString);

	// Echo Input
	printf("%s\n", currentCommandString);
	
    if(strcmp(currentCommandString, "QUIT") == 0)
    {
      break;
    }
    // Identify Callback
	if(strstr(currentCommandString, " ") == 0)
	{ // No spaces, so all opcode
      // printf("No spaces\n");
	  strcpy((char*)&currentOpcodeString, (char*)&currentCommandString);
	  currentOperandsPtr = NULL;
	}
	else
	{
	  strncpy((char*)&currentOpcodeString, (char*)&currentCommandString, (strchr(currentCommandString, ' ') - currentCommandString));
	  strcpy((char*)&currentOperands, (char*)&currentCommandString +(strchr(currentCommandString, ' ') - currentCommandString));
      currentOperandsPtr = &currentOperands[0];
	  // printf("currentOpcodeString: %s\n", currentOpcodeString);
	  // printf("currentOperands: %s\n", currentOperands);
	}

	uint8_t i = 0;
	while((commandInterfaces[i] != NULL) && 
	       (strcmp(currentOpcodeString, commandInterfaces[i]->commandString) != 0))
	{
	  i += 1;
	}
	if(commandInterfaces[i] == NULL)
	{
	  printf("Invalid Command: '%s'\n", currentCommandString);
	}
    // Verify Parameters
	else
	{
	  if(commandInterfaces[i]->validate(currentOperandsPtr))
	  {
		// printf("currentOperands: %s\n", currentOperands);
		commandInterfaces[i]->execute(currentOperands);
	  }
	  else
	  {
		printf("Invalid Operands: %s.\n", currentOperandsPtr);
	  }
		  
	}
    // Perform Operation
  }

  printf("Exiting Hardware Evaluation Mode.\n");

  return 0;

}
