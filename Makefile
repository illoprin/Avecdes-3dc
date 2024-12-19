
CC=gcc # using C compiler

CFLAGS=-Wall -std=c99 # Enable all warnings, use C99 ANSI standart

TARGET=bin/app

TARGET_TEST=bin/test

TEST_SRC?=_sketches/test.c # test file source default value

SRCS=$(shell find src -name '*.c') # find all source files

INCLUDE_PATH=include

LIBS_PATH=libs

# lm - math lib
# lGLFW - OpenGL window
# lGLU - OpenGL utils 
# lGL - OpenGL
LIBS=-lm -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lGLEW

run:
	$(CC) $(CFLAGS) -DGLEW_STATIC -g $(SRCS) -I $(INCLUDE_PATH) -L $(LIBS_PATH) -o $(TARGET) $(LIBS)
	./$(TARGET)

test:
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TARGET_TEST) -lm
	./$(TARGET_TEST)