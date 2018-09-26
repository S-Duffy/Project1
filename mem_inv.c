


#include "command_interface.h"
int MemInvValidate(char* params);
int MemInvExecute(char* params);

COMMAND_INTERFACE_STRUCT MemInvCommandInterface =
{
	"MINV",
	"Frees the block of memory allocated by MALL. Takes no arguments Ex: MFRE",
	MemInvValidate,
	MemInvExecute,
};


int MemInvValidate(char* params)
{
	return 1;
}

int MemInvExecute(char* params)
{
	return 1;
}