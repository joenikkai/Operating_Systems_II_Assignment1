CC ?= gcc
FLAGS ?= 
IFLAGS ?=
IFLAGS := -I./
FLAGS := -std=c99 $(FLAGS) $(IFLAGS)
LDFLAGS ?= 
LDFLAGS :=  -lreadline $(LDFLAGS)
BINARY ?= Operating_Systems_II_Assignment1

SOURCES ?= $(shell find . -name "*.c")
OBJECTS := $(SOURCES:%.c=%.o)

.PHONY: all clean run

all: $(BINARY)
	@echo "compilation complete"

%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(FLAGS) $(LDFLAGS)

run: $(BINARY)
	./$<

clean:
	@rm $(OBJECTS) $(BINARY)
	@echo "DELETED: $(OBJECTS) $(BINARY)"
