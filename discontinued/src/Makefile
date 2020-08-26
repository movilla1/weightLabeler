SHELL = /bin/sh

OBJS = main.o main_menu.o common.o pesaje.o articulo.o listar_articulos.o dialogo.o crear_articulo.o modificar_articulo.o db_interface.o
CFLAGS = -Wall -g -Wno-write-strings
CC = g++
H_DEPS = common.h db_interface.h dialogo.h
INCLUDES = -I/usr/local/include/glbarcode++-0/
LIBS = -lncurses -lmenu -lform -lgbc-0 -L/usr/local/lib -lsqlite3
BINS = weightLabeler dbinit

weightLabeler: ${OBJS}
		${CC} ${CFLAGS} ${INCLUDES} ${OBJS} -o ../bin/$@ ${LIBS}

db_init:
		${CC} ${CFLAGS} ${INCLUDES} db_init.cpp -o ../bin/$@ ${LIBS}

.cpp.o: ${H_DEPS}
		$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
		-rm *.o ../bin/*

all: ${BINS}