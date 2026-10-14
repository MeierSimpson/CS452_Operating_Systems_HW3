CC ?= gcc

CPPFLAGS += -Ihw1
CFLAGS += -std=gnu11 -Wall -Wextra -g
LDLIBS += -lreadline -lncurses

sources := Command.c Interpreter.c Jobs.c Parser.c Pipeline.c \
           Scanner.c Sequence.c Shell.c Tree.c
objects := $(sources:.c=.o)

.PHONY: all clean test trytest valgrind

all: shell

shell: $(objects) libdeq.so
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(objects) \
	    -L. -Wl,-rpath,'$$ORIGIN' -ldeq $(LDLIBS)

# Keep the name used by the original skeletal makefile available.
try: $(objects) libdeq.so
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(objects) \
	    -L. -Wl,-rpath,'$$ORIGIN' -ldeq $(LDLIBS)

libdeq.so: hw1/deq.c hw1/deq.h hw1/error.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -shared -o $@ hw1/deq.c

test: shell
	bash Test/run shell

trytest: try
	bash Test/run try

valgrind: shell
	bash ./vg

clean:
	rm -f $(objects) shell try libdeq.so

Parser.o: CFLAGS += -Wno-unused-function
