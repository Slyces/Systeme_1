#ifdef CHANGED
  #include "copyright.h"
  #include "system.h"
  #include "synchconsole.h"
  #include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;


static void ReadAvailHandler(void *arg) {
    (void)arg; readAvail->V();
}

static void WriteDoneHandler(void *arg) {
    (void)arg; writeDone->V();
}

SynchConsole::SynchConsole(const char *in, const char *out) {
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console   = new Console(in, out, ReadAvailHandler, WriteDoneHandler, 0);
}

SynchConsole::~SynchConsole() {
    delete console;
    delete writeDone;
    delete readAvail;
}

void SynchConsole::SynchPutChar(int ch) {
    console->PutChar(ch);
    writeDone->P();
}

// @TODO vérifier mon erreur
int SynchConsole::SynchGetChar() {
    readAvail->P(); // wait for character to arrive
    return console->GetChar();
}

void SynchConsole::SynchPutString(const char *s) {
    // for (unsigned int i = 0; i < sizeof(s); i++) {
    //     SynchPutChar(s[i]);
    // }
    int i = 0;

    while (s[i] != '\0') {
        SynchPutChar(s[i]);
        i++;
    }
}

  #if 1
void SynchConsole::SynchGetString(char *s, int n) {
    int  i = 0;
    char c;

    while (i < n && c != EOF && c != '\n') {
        c    = SynchGetChar();
        s[i] = c;
        i++;
    }
    s[i] = '\0';
}

  #endif // if 0
#endif   // CHANGED
