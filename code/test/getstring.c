#include "syscall.h"

int main();
void mafonction();

int main()
{
  int maxsize = 50;
  char string[maxsize];
  PutString("Bonjour ! Saisissez un chaîne");
  PutString(" (50 char max)!\n");
  GetString(string, maxsize);
  PutString("\nEst-ce que c'était : \n<< ");
  PutString(string);
  PutString(" >> ?\n");
  return 0;
}
