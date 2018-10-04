/************************************************************************
 *
 * File: command_interface.c
 * Description: Header for command interface organization and helper
 *              functions to interpret commands.
 * 
 * Author: Sean Duffy
 * Tools: gcc
 * Leveraged Code: See "#include"s
 * Links: NA
 *
***********************************************************************/


#include "stdint.h"
#include "string.h"
#include "stdio.h"

uint64_t decPlaceValues[] = {
	1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000
};

uint64_t hexPlaceValues[] = {
	1, 16, 256, 4096, 65536, 1048576, 16777216, 268435456, 4294967296, 68719476736, 1099511627776, 17592186044416, 281474976710656, 4503599627370496, 72057594037927936
};

uint64_t* placeValues;

uint64_t convStringToNum(char* numberString)
{
  uint64_t integer = 0;
  
  if(numberString[0] == '0')
  {
	if(numberString[1] == 'x')
	{
      placeValues = hexPlaceValues;
	  numberString += 2;
	}
	else
	{
      placeValues = decPlaceValues;
	}
  }
  else
  {
    placeValues = decPlaceValues;
  }
	
  for(uint8_t i = 0; i <strlen(numberString) ; i+= 1)
  {
    integer += (numberString[i] - '0') * placeValues[strlen(numberString) - i - 1];
	// printf("i: %d, integer: %d\n", i , integer);
	fflush(stdout);
  }

  return integer;
}

uint8_t isValidNum(char* inputString)
{
  uint8_t isHex = 0;
  
  for(uint8_t i = 0; i <strlen(inputString); i += 1)
  {
	if((i == 0) && inputString[i] == '0')
	{
      isHex += 1;
	}
	else if((i == 1) && inputString[i] == 'x')
	{
      isHex += 1;
	  if(strlen(inputString) <= 2)
	  {
        return 0;
	  }
	}
	else if((isHex != 2) && ((inputString[i] > '9') || (inputString[i] < '0')) ||
	        ((isHex == 2) && ((inputString[i] > '9') || (inputString[i] < '0') &&
			                ((inputString[i] > 'f') || (inputString[i] < 'a')))))
	  return 0;
  }
  return 1;
  
}
