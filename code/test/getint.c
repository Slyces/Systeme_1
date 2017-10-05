#include "syscall.h"

int main()
{
    // char test[4];
    int test[1];
    PutString("Test de GetInt (syscall).\n");
    GetInt((int *) test);
    PutString("La nouvelle valeur de Robert est : ");
    // PutInt((char *) *test);
    PutInt(*test);
    PutChar('.');
    return 1;
}
