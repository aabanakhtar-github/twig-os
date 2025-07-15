#ifndef SHELL_H
#define SHELL_H

#include "stdbool.h"
#include "tcontainers.h"

bool shellRun(TString* command);
// builtins
void about(void);
void clear(void);
void help(void);
void reboot(void);
void echo(void);
void ls(void);
void touch(void);
void write(void);
void cat(void);
void rm(void);
void meminfo(void);

#endif // SHELL_H