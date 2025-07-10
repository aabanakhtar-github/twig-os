#ifndef SHELL_H
#define SHELL_H

#include "stdbool.h"
#include "tcontainers.h"

bool shellRun(TString* command);
// builtins
void about(void);
void clear(void);
void reboot(void);
void echo(void);

#endif // SHELL_H