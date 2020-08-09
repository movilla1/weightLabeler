SHELL = /bin/sh

OBJS =  main.o main_menu.o common.o pesaje.o
CFLAGS = -Wall -g -Wno-write-strings
CC = g++
INCLUDES =
LIBS = -lncurses -lmenu

weightLabeler: ${OBJS}
		${CC} ${CFLAGS} ${INCLUDES} ${OBJS} -o bin/$@ ${LIBS}

.cpp.o:
		$(CC) $(CFLAGS) -c $<

clean:
		-rm *.o bin/*

all: weightLabeler