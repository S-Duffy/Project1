/************************************************************************
 *
 * File: command_interface.h
 * Description: Header for command interface organization and helper
 *              functions to interpret commands.
 * 
 * Author: Sean Duffy
 * Tools: gcc
 * Leveraged Code: See "#include"s
 * Links: NA
 *
***********************************************************************/
#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include "stdint.h"

typedef uint8_t (*commandValidationFunc)(char* params);
typedef void (*commandExecuteFunc)(char* params);


typedef struct {
  const char* commandString;
  const char* commandHelpString;
  commandValidationFunc validate;
  commandExecuteFunc execute;
} COMMAND_INTERFACE_STRUCT;

/**
 * Name: convStringToNum
 * Description: 
 * Argurments: char* numberString - ASCII string of a decimal or hexadecimal number
 * Return Value: integer (in 2's complement) that corresponds to given string
 *
 */
uint64_t convStringToNum(char* numberString);

/**
 * Name: isValidNum
 * Description: Determines if input string represents a valid decimal or hexadecimal number
 * Argurments: char* inputString - ASCII string
 * Return Value: uint8_t (boolean) 0: string is not a valid decimal or hexadecimal number
 *                                 1: string is a valid decimal or hexadecimal number
 */
uint8_t isValidNum(char* inputString);

#endif

