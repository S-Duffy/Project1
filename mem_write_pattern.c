

#include "command_interface.h"
int MemWritePatternValidate(char* params);
int MemWritePatternExecute(char* params);
COMMAND_INTERFACE_STRUCT MemWritePatternCommandInterface =
{
	"MWPA",
	"Write a pattern to a memory block designated by start address and size. Ex: 0x12345678 100",
	MemWritePatternValidate,
	MemWritePatternExecute,
};


int MemWritePatternValidate(char* params)
{
	return 1;
}

int MemWritePatternExecute(char* params)
{
	return 1;
}