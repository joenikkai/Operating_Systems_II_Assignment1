
CC ?= 

ifndef $(CC)
CC := gcc
endif

BINARY ?= 

ifndef BINARY
  BINARY := Operating_Systems_II_Assignment1
endif


# This flag is enabled so that we can pass the -DTEST_THIS_CODE flag
MACROS_FLAGS ?=
MACROS_FLAGS := $(MACROS_FLAGS)

IFLAGS ?=
IFLAGS := -I./

FLAGS ?= 
FLAGS := -std=gnu99 $(FLAGS) $(IFLAGS) $(MACROS_FLAGS) $(WGWFLAGS)

LDFLAGS ?= 
LDFLAGS := -lncurses $(LDFLAGS) $(WGWLDFLAGS)

SOURCES ?= $(shell find . -name "*.c")
OBJECTS := $(SOURCES:%.c=%.o)

.PHONY: all clean run help

all: $(BINARY)
	@echo "Compilation complete"

%.o: %.c
	@echo "COMPILING: $<"
	@$(CC) -o $@ -c $< $(FLAGS)

$(BINARY): $(OBJECTS)
	@echo "LINKING: $^"
	$(CC) -o $@ $^ $(FLAGS) $(LDFLAGS)

run: $(BINARY)
	@echo "RUNNING: $<"
	./$<

clean:
	@rm -fr $(OBJECTS) $(BINARY)
	@echo "DELETED: $(OBJECTS) $(BINARY)"

help:
	@echo "`make` to compile"
	@echo flags are clean run
