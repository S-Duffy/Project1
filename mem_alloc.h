/************************************************************************
 *
 * File: mem_alloc.h
 * Description: Header file that defines the interface to the implementation
 *              of the allocate memory block command and the information
 *              describing the allocated memory block
 * 
 * Author: Sean Duffy
 * Tools: gcc
 * Leveraged Code: See "#include"s
 * Links: NA
 *
***********************************************************************/
#ifndef MEM_ALLOC_H
#define MEM_ALLOC_H


extern COMMAND_INTERFACE_STRUCT MemAllocCommandInterface;

extern uint32_t* memBlockPtr;
extern uint32_t memBlockSizeBytes;

#endif
