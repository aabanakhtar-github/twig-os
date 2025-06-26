#ifndef SHELL_H
#define SHELL_H

#include "stdbool.h"

bool shellRun(const char* command);
// builtins
void about(void);
void clear(void);
void reboot(void);

#endif // SHELL_H