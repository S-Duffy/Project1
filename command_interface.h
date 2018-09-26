// command_interface.h
//
//
//
//
//
#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include "stdint.h"

typedef uint8_t (*commandValidationFunc)(char* params);
typedef uint8_t (*commandExecuteFunc)(char* params);


typedef struct {
  const char* commandString;
  const char* commandHelpString;
  commandValidationFunc validate;
  commandExecuteFunc execute;
} COMMAND_INTERFACE_STRUCT;


#endif

