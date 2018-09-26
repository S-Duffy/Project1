// command_interface.h
//
//
//
//
//
#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H


typedef int (*commandValidationFunc)(char* params);
typedef int (*commandExecuteFunc)(char* params);


typedef struct {
  const char* commandString;
  const char* commandHelpString;
  commandValidationFunc validate;
  commandExecuteFunc execute;
} COMMAND_INTERFACE_STRUCT;


#endif

