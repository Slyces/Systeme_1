#include "syscall.h"

int main()
{
    PutString("Test de PutInt (syscall).\n");
    PutString("int 65421 >> ");
    PutInt(65421);
    PutString("\nint -65421 >> ");
    PutInt(-65421);
    PutString("\nint 321665465421 >> ");
    PutInt(321665465421);
    PutString("\nlong 321665465421 >> ");
    PutInt((long) 321665465421);
    PutString("\nlong -321665465421 >> ");
    PutInt((long) -321665465421);
    // Halt();
}
