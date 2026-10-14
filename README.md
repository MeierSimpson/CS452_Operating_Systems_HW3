# CS 452 Homework 3 baseline

This repository contains the provided shell skeleton for the non-CS 552
requirements. The CS 552-only compound commands, subshells, and job-control
commands are intentionally not included in these baseline instructions.

## Prerequisites

Install the C compiler, GNU Make, GNU Readline, GNU ncurses, and Valgrind
development/runtime packages. On Debian or Ubuntu, the packages are commonly
available with:

```sh
sudo apt install build-essential libreadline-dev libncurses-dev valgrind
```

## Build

From the repository root:

```sh
make
```

This builds:

* `shell`, the shell executable
* `libdeq.so`, the shared deque library built from `hw1/deq.c`
* the object files for the shell modules

The executable records a relative runtime search path for `libdeq.so`, so it
can be run directly from the repository root without setting `LD_LIBRARY_PATH`.

The original skeleton called the executable `try`. That name remains available
when needed:

```sh
make try
```

## Run interactively

```sh
./shell
```

Enter commands such as `pwd`, `cd /tmp`, `cd -`, `history`, `sleep 5 &`, and
`cat < input.txt > output.txt`. Commands separated by `|` form a pipeline,
such as `cat input.txt | wc -l`. A command followed by `&` runs in the
background; the shell continues reading commands and waits for remaining
background commands before exiting. Press `Ctrl-D` or use
the `exit` builtin to leave the shell. Interactive history is stored in
`.history`.

To run commands from a file or standard input:

```sh
printf 'pwd\nexit\n' | ./shell
```

## Run the regression tests

The provided regression runner is available through Make:

```sh
make test
```

It runs `Test/run shell`, which executes every `Test/Test_*/inp` file and
compares the output with its corresponding `exp` file. The original executable
name is also supported:

```sh
make trytest
```

To add a test, create a new `Test/Test_<name>/` directory containing `inp` and
the expected `exp` output.

## Check memory usage

```sh
make valgrind
```

This uses the supplied `vg` script and `rl.supp` suppressions. The baseline
shell is skeletal; memory and behavior issues in the assignment implementation
are expected to be addressed as development proceeds.

## Clean generated build files

```sh
make clean
```
