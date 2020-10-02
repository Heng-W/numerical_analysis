
CC=gcc
CFLAGS= -std=c99 -lm -Wall -O2 -fexec-charset=gbk

TARGET_DIR:=build
SRCS:=$(wildcard *.c)
TARGETS:=$(patsubst %.c,$(TARGET_DIR)/%.exe,$(SRCS))


.PHONY: all clean

all: $(TARGET_DIR) $(TARGETS)

$(TARGET_DIR):
	mkdir -p $@

$(TARGET_DIR)/%.exe: %.c
	@echo compile $^
	$(CC) $(CFLAGS) $^ -o $@ 
	@echo

clean:
	rm -rf build/
    