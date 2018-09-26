



#include "command_interface.h"
int MemAllocValidate(char* params);
int MemAllocExecute(char* params);

COMMAND_INTERFACE_STRUCT MemAllocCommandInterface =
{
	"MALL",
	"Allocates a block of memory. Takes 1 argument to determine size. Ex: MALL 100",
	MemAllocValidate,
	MemAllocExecute,
};


int MemAllocValidate(char* params)
{
	return 1;
}

int MemAllocExecute(char* params)
{
	return 1;
}