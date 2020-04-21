
CFLAGS = -Wall -g -DLINUX -D_REENTRANT -Werror=implicit-function-declaration

LDLIBS = -lpicmlx -lpiplx

all : TestCB
TestCB: TestCB.o
TestCB.o : TestCB.c

.PHONY: rebuild
rebuild: clean TestCB

.PHONY: clean
clean:
	rm -f TestCB TestCB.o

.PHONY: release
release:
	cd .. && tar cvzf test-cb-src.tar.gz ./src/Makefile ./src/*.c

