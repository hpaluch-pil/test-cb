# Makefile - for TestCB
CFLAGS = -Wall -g -DLINUX -D_REENTRANT -Werror=implicit-function-declaration

LDLIBS = -lpicmlx -lpiplx

all : TestCB
TestCB : TestCB.o
TestCB.o : TestCB.c

.PHONY: rebuild
rebuild: clean TestCB

.PHONY: clean
clean:
	rm -f TestCB TestCB.o

git_ver=$(shell scripts/setlocalversion)
a=test-cb$(git_ver).tar.gz

.PHONY: release
release:
	cd .. && tar -czf $(a) ./test-cb/Makefile ./test-cb/*.c ./test-cb/README.md ./test-cb/scripts

