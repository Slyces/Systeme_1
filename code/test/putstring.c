#include "syscall.h"

int main()
{
    PutString("Bonjour ! Test 1 !\n");
    PutString("Incroyable ! Une fin de stri\0g au milieu d'un string ? oO");
    PutString("\n");
    PutString("abcdefghijklmnopqrstuvwxyz0123456789\n");
    PutString("\n5 est le 32e caractère. ");
    PutString("Or, MAX_STRING_SIZE est à 32.");
    PutString(", donc la taille est correctemen");
    PutString("t limitée\n");
    PutString("Avec un maxstring flottant");
    PutString(", on a des erreurs de mémoire");
    PutString("\n...\n\n");
    // Halt();
}
