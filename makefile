CC ?= gcc

# This flag is enabled so that we can pass the -DTEST_THIS_CODE flag
MACROS_FLAGS ?=
MACROS_FLAGS := $(MACROS_FLAGS)

IFLAGS ?=
IFLAGS := -I./

FLAGS ?= 
FLAGS := -std=c99 $(FLAGS) $(IFLAGS) $(MACROS_FLAGS)

LDFLAGS ?= 
LDFLAGS :=  -lreadline $(LDFLAGS)

BINARY ?= Operating_Systems_II_Assignment1

SOURCES ?= $(shell find . -name "*.c")
OBJECTS := $(SOURCES:%.c=%.o)

.PHONY: all clean run

all: $(BINARY)
	@echo "Compilation complete"

%.o: %.c
	@echo "COMPILING: $<"
	@$(CC) -o $@ -c $< $(FLAGS)

$(BINARY): $(OBJECTS)
	@echo "LiNKING: $<"
	@$(CC) -o $@ $^ $(FLAGS) $(LDFLAGS)

run: $(BINARY)
	@echo "RUNNING: $<"
	./$<

clean:
	@rm $(OBJECTS) $(BINARY)
	@echo "DELETED: $(OBJECTS) $(BINARY)"
