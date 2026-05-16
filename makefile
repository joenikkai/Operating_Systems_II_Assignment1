# i used \x86_64-w64-mingw32-gcc and \x86_64-redhat-linux-gcc for this project
CC ?= 

ifndef $(CC)
CC := gcc
endif

BINARY ?=

ifndef $(BINARY)
	ifeq ( $(CC), x86_64-w64-mingw32-gcc )
	$(info cross compiling for windows)
	# posix wrapper
	WGWFLAGS = -static 
	WGWLDFLAGS = -lpcre2-posix 
	BINARY := Operating_Systems_II_Assignment1.exe
	else
	BINARY := Operating_Systems_II_Assignment1
	endif
endif


# This flag is enabled so that we can pass the -DTEST_THIS_CODE flag
MACROS_FLAGS ?=
MACROS_FLAGS := $(MACROS_FLAGS)

IFLAGS ?=
IFLAGS := -I./

FLAGS ?= 
FLAGS := -std=gnu99 $(FLAGS) $(IFLAGS) $(MACROS_FLAGS) $(WGWFLAGS)

LDFLAGS ?= 
LDFLAGS :=  -lreadline $(LDFLAGS) $(WGWLDFLAGS)

SOURCES ?= $(shell find . -name "*.c")
OBJECTS := $(SOURCES:%.c=%.o)

.PHONY: all clean run

all: $(BINARY)
	@echo "Compilation complete"

%.o: %.c
	@echo "COMPILING: $<"
	@$(CC) -o $@ -c $< $(FLAGS)

$(BINARY): $(OBJECTS)
	@echo "LINKING: $^"
	@$(CC) -o $@ $^ $(FLAGS) $(LDFLAGS)

run: $(BINARY)
	@echo "RUNNING: $<"
	./$<

clean:
	@rm $(OBJECTS) $(BINARY)
	@echo "DELETED: $(OBJECTS) $(BINARY)"
