#ifndef COMMAND_H
#define COMMAND_H

#include <sys/types.h>

typedef void *Command;

#include "Tree.h"
#include "Jobs.h"
#include "Sequence.h"

extern Command newCommand(T_command command);

extern void execCommand(Command command, Pipeline pipeline, Jobs jobs,
			int *jobbed, int *eof, int fg, int input_fd,
			int output_fd, int wait_for_child, pid_t *pid);

extern void freeCommand(Command command);
extern void freestateCommand();

#endif
