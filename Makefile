CC=gcc
OPTS= -g -Wall -Wextra
OBJ= ab.o
PROG=tp_avl

all: ${PROG}

${PROG}: tp_AVL.c ${OBJ}
	${CC} ${OBJ} tp_AVL.c -o ${PROG} ${OPTS}

${OBJ}: ab.c ab.h
	${CC} -c ab.c ${OPTS}

clean: 
	rm tp_avl *.o
