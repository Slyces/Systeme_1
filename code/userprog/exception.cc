// exception.cc

//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

#ifdef CHANGED
# include <stdlib.h>
#endif // ifdef CHANGED

// ----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
// ----------------------------------------------------------------------
static void
UpdatePC()
{
    int pc = machine->ReadRegister(PCReg);

    machine->WriteRegister(PrevPCReg, pc);
    pc = machine->ReadRegister(NextPCReg);
    machine->WriteRegister(PCReg,     pc);
    pc += 4;
    machine->WriteRegister(NextPCReg, pc);
}

// ----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions
//      are in machine.h.
// ----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    switch (which)
    {
    case SyscallException:
    {
        switch (type)
        {
        case SC_Halt:
        {
            DEBUG('s', "Shutdown, initiated by user program.\n");
            interrupt->Halt();
            break;
        }

        #ifdef CHANGED
        case SC_PutChar:
        {
            DEBUG('s', "PutChar\n");
            int c = machine->ReadRegister(4); // information stockée dans r4
            synchconsole->SynchPutChar(c);
            break;
        }

        case SC_PutString:
        {
            // @TODO Si taille flottante, faire en plusieurs fois.
            DEBUG('s', "PutString\n");
            int   adress = machine->ReadRegister(4);
            char *string = (char *)malloc(MAX_STRING_SIZE * sizeof(char));
            copyStringFromMachine(adress, string, MAX_STRING_SIZE);
            synchconsole->SynchPutString(string);
            free(string);
            break;
        }

        case SC_GetChar:
        {
            DEBUG('s', "GetChar\n");
            int c = synchconsole->SynchGetChar();
            machine->WriteRegister(2, c); // registre utilisé pour le retour
                                          // d'une valeur à la fin d'une
                                          // fonction est le registre 2
            break;
        }

        case SC_GetString:
        {
            DEBUG('s', "GetString\n");
            unsigned int adress = machine->ReadRegister(4);
            int n               = machine->ReadRegister(5);

            // char * string = (char *) malloc(n * sizeof(char));
            char string[n];
            synchconsole->SynchGetString(string, n);
            copyStringToMachine(string, adress, n);

            // free(string);
            break;
        }

        case SC_PutInt:
        {
            DEBUG('s', "PutInt\n");
            int k    = machine->ReadRegister(4);
            int size = (8 * sizeof(k)) / 3 + 1; // always > to the number of
                                                // digits of the larger
            char buffer[size];                  // int that can be encoded
            snprintf(buffer, size, "%d", k);
            synchconsole->SynchPutString(buffer);
            break;
        }

        case SC_GetInt:
        {
            DEBUG('s', "GetInt\n");
            int *k = machine->ReadRegister(4);
            
            break;
        }

        case SC_Exit:
        {
            DEBUG('s', "Exit\n");
            interrupt->Exit();
            break;
        }
        #endif // CHANGED

        default:
        {
            printf("Unimplemented system call %d\n", type);
            ASSERT(FALSE);
        }
        }

        // Do not forget to increment the pc before returning!
        UpdatePC();
        break;
    }

    case PageFaultException:

        if (!type) {
            printf("NULL dereference at PC %x!\n", machine->registers[PCReg]);
            ASSERT(FALSE);
        } else {
            printf("Page Fault at address %x at PC %x\n",
                   type,
                   machine->registers[PCReg]);
            ASSERT(FALSE); // For now
        }

    default:
        printf("Unexpected user mode exception %d %d at PC %x\n",
               which,
               type,
               machine->registers[PCReg]);
        ASSERT(FALSE);
    }
}
