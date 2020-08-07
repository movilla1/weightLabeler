SHELL = /bin/sh

OBJS =  main.o main_menu.o
CFLAG = -Wall -ggdb -Wpermissive
CC = g++
INCLUDES =
LIBS = -lncurses -lmenu

weightLabeler: ${OBJS}
		${CC} ${CFLAGS} ${INCLUDES} -o bin/$@ ${OBJS} ${LIBS}

.o:
		$(CC) $(CFLAGS) -c $<

clean:
		-rm *.o bin/*