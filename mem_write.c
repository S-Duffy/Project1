
#include "command_interface.h"

int MemWriteValidate(char* params);
int MemWritenExecute(char* params);

COMMAND_INTERFACE_STRUCT MemWriteCommandInterface =
{
	"MWRT",
	"Write a 4 byte value to a memory address. Ex: MWRT 0x12345678 42",
	MemWriteValidate,
	MemWritenExecute,
};


int MemWriteValidate(char* params)
{
	return 1;
}

int MemWritenExecute(char* params)
{
	return 1;
}
