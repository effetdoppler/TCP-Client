CC = gcc
CFLAGS = -Wall -Wextra
CPPFLAGS = -MMD

all: main

#main: main.o print_page.o
#main.o: main.c print_page.h
#print_page.o: print_page.c print_page.h

SRC = main.c print_page.c
OBJ = ${SRC:.c=.o}
# add list of dependency files
DEP = ${SRC:.c=.d}


main: ${OBJ}
# include dependency files
-include ${DEP}

.PHONY: clean

clean:
	${RM} main ${OBJ} ${DEP}
