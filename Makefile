## PPF-Tool Makefile
## Sorry for this shitty Makefile. I hate Makefiles.
## In fact this is the lamest Makefile on earth and make SUXX BIGTIME.

# Please take a look into LFS.h and adapt this line and/or LFS.h to have
# proper 64 Bit I/O support. If you are using for example MacOSX change
# the line below to -DMACOSX
LFSFLAG = -DLINUX

CC 	= g++
CFLAGS	= -O2 -Wall ${LFSFLAG} -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
BINNAME	= ppftool
OBJCOPY	= objcopy
OBJS	= main.o \
	  CParameter.o \
	  CEndian.o \
	  CPPF.o \
	  CPPF10.o \
	  CPPF20.o \
	  CPPF30.o

all: ppftool

clean:
	rm -f *.o ${BINNAME}

ppftool: ${OBJS}
	${CC} -s -o ${BINNAME} ${OBJS}
	${OBJCOPY} -S ${BINNAME}

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $*.o 

