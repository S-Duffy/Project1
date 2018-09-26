
#include "command_interface.h"
int MemVerPatternValidate(char* params);
int MemVerPatternExecute(char* params);

COMMAND_INTERFACE_STRUCT MemVerPatternCommandInterface =
{
	"MVPA",
	"Verifies Pattern matches the memory space designated by address and size. Ex MVPA 0x12345678 100",
	MemVerPatternValidate,
	MemVerPatternExecute,
};


int MemVerPatternValidate(char* params)
{
	return 1;
}

int MemVerPatternExecute(char* params)
{
	return 1;
}