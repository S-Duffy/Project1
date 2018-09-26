


#include "command_interface.h"
int MemFreeValidate(char* params);
int MemFreeExecute(char* params);

COMMAND_INTERFACE_STRUCT MemFreeCommandInterface =
{
	"MFRE",
	"Frees the block of memory allocated by MALL. Takes no arguments Ex: MFRE",
	MemFreeValidate,
	MemFreeExecute,
};


int MemFreeValidate(char* params)
{
	return 1;
}

int MemFreeExecute(char* params)
{
	return 1;
}