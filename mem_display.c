


#include "command_interface.h"
int MemDisplayValidate(char* params);
int MemDisplayExecute(char* params);

COMMAND_INTERFACE_STRUCT MemDisplayCommandInterface =
{
	"MDIS",
	"Displays a block of memory. Takes 2 arguments: Starting Address and Size (in 4 byte words). Ex: MDIS 0x12345678 100",
	MemDisplayValidate,
	MemDisplayExecute,
};


int MemDisplayValidate(char* params)
{
	return 1;
}

int MemDisplayExecute(char* params)
{
	return 1;
}