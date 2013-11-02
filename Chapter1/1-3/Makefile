SRC := ${wildcard *.c}
TARGET = $(SRC:.c=)
OBJECTS = $(SRC:.c=.o)

# simple enumeration
#TARGET = target
#OBJECTS = ${TARGET}.o

# multiobject build
#OBJECTS +=

# debug symbols
#CFLAGS ?= -g
CFLAGS ?= -O2
CFLAGS += -Wall -fPIC
#CFLAGS += -I...

# shared libraries
#LDFLAGS += -L... -l...

# static build
#LDFLAGS += -static
#LIBS += ...

all: ${TARGET}

${TARGET}: ${OBJECTS} ${LIBS} Makefile
	${CC} ${LDFLAGS} ${OBJECTS} ${LIBS} -o ${TARGET}

%.o: %.c Makefile
	${CC} -c ${CFLAGS} $< -o $@

cscope:
	ls -1f *.[hc] > cscope.files
	cscope -b -k -i cscope.files

tags:
	ctags *.[hc]

help:
	head -n 9 ${TARGET}.c

clean:
	rm -f *.o ${TARGET}
	rm -f cscope.* tags

.PHONY: all clean cscope tags help
.DELETE_ON_ERROR:
