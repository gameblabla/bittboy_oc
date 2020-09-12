# gpSP makefile
# Gilead Kutnick - Exophase

# Global definitions

CC        = gcc
OBJS      = main.o
BIN       ?= bittboy 

# Platform specific definitions 

VPATH      += ..
CFLAGS     += -O2 -g
INCLUDES   = -I.
LIBS       = -lc -lgcc

# Compilation:

all:	${BIN}

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c -o $@ $<

${BIN}:	${OBJS}
	${CC} ${OBJS} ${LIBS} -o ${BIN}  

clean:
	rm -f *.o ${BIN} 

