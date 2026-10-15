## Build

From the repository root:

```sh
make
```

This builds:

* `shell`, the shell executable
* `libdeq.so`, the shared deque library built from `hw1/deq.c`
* the object files for the shell modules


## Run interactively

```sh
./shell
```

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
compares the output with its corresponding `exp` file.

## Check memory usage

```sh
make valgrind
```
## Clean generated build files

```sh
make clean
```
