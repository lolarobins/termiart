# release information
VERSION=0.0.1
TARGET=termiart

# install location
PREFIX?=/usr/local
INSTALL_BIN=$(PREFIX)/bin

# c compiler
CC=gcc
CLIBS=-lpng
CFLAGS=-g -Wall -Iinclude $(CLIBS) -D_PROG_VERSION=\"$(VERSION)\" 

OBJS:=$(patsubst src/%.c,bin/%.o,$(shell find src -name '*.c'))

all: ${TARGET}

install: $(TARGET)
	cp $(TARGET) $(INSTALL_BIN)/$(TARGET)

$(TARGET): $(OBJS)
	@-mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

bin/%.o: src/%.c
	@-mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf bin
