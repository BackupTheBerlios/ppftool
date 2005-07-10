## PPF-Tool Makefile
## Sorry for this shitty Makefile. I hate Makefiles.
## In fact this is the lamest Makefile on earth and make SUXX BIGTIME.

CC = g++
CFLAGS = -O2 -Wall -DLINUX -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
BINNAME = ppftool
OBJCOPY = objcopy

all:	ppftool

clean:
	rm -f *.o ${BINNAME}

ppftool:	main.o CParameter.o CEndian.o CPPF.o CPPF10.o
	${CC} -s -o ${BINNAME} main.o CParameter.o CEndian.o CPPF.o CPPF10.o
	${OBJCOPY} -S ${BINNAME}

main.o:	main.cpp
	${CC} -c main.cpp -o main.o ${CFLAGS}

CParameter.o:	CParameter.cpp
	${CC} -c CParameter.cpp -o CParameter.o ${CFLAGS}

CEndian.o:	CEndian.cpp
	${CC} -c CEndian.cpp -o CEndian.o ${CFLAGS}

CPPF.o:	CPPF.cpp
	${CC} -c CPPF.cpp -o CPPF.o ${CFLAGS}

CPPF10.o:	CPPF10.cpp
	${CC} -c CPPF10.cpp -o CPPF10.o ${CFLAGS}

