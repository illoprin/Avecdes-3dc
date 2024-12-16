
CC=gcc # using C compiler

CFLAGS=-Wall -std=c99 # Enable all warnings, use C99 ANSI standart

TARGET=bin/app

TARGET_TEST=bin/test

TEST_SRC=_sketches/test.c # test file source

SRCS=$(shell find src -name '*.c') # find all source files

INCLUDE_PATH=include

LIBS_PATH=libs

LIBS=-lm # lm - math lib

run:
	$(CC) $(CFLAGS) -g $(SRCS) -I $(INCLUDE_PATH) -L $(LIBS_PATH) -o $(TARGET) $(LIBS)
	./$(TARGET)

test:
	$(CC) $(CFLAGS) $(TEST_SRC) -I $(INCLUDE_PATH) -L $(LIBS_PATH) -o $(TARGET_TEST) $(LIBS)
	./$(TARGET_TEST)