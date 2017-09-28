#include "syscall.h"

int main()
{
    PutString("Bonjour ! Test 1 !\n");
    PutString("Incroyable ! Une fin de stri\0g au milieu d'un string ? oO");
    PutString("\n");
    PutString("abcdefghijklmnopqrstuvwxyz0123456789\n");
    PutString("\nLe string ci-dessus a initialement 36 caractères.");
    Halt();
}
