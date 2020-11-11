
CC=gcc
CFLAGS= -std=c99 -Wall -O2
LINKFLAGS:= -lm

TARGET_DIR:=build
SRCS:=$(wildcard *.c)
TARGETS:=$(patsubst %.c,$(TARGET_DIR)/%,$(SRCS))


.PHONY: all clean

all: $(TARGET_DIR) $(TARGETS)

$(TARGET_DIR):
	mkdir -p $@

$(TARGET_DIR)/%: %.c
	@echo compile $^
	$(CC) $(CFLAGS) $^ -o $@ $(LINKFLAGS)
	@echo

clean:
	rm -rf build/
