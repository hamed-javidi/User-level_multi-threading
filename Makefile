#Hamed Javidi, Azin Shamshirgaran
#2738776, 2729460
#Date of creation: 2/28/2020
#Date of modification 3/5/2020

#
# Makefile for building xthreads library on i386
#
# Maintain the following definition:
#	HFILES	all header files (*.h) programmer created
#	SFILES	all C source files (*.c) programmer created
#	OFILES	all object files (*.o) required to load program
#
# Use the following make targets:
#	depend	to update header file dependencies

.DEFAULT:
	co -q $@

HFILES = proc.h 
#yeild.c and yield.o are removed and join.cand join.o are added
CFILES = create.c resched.c main.c join.c xmain.c
SFILES = ctxsw.s 
#join.o is added
OFILES = create.o ctxsw.o resched.o main.o join.o
XTLIB  = ./libxt.a
APP_CFILES = xmain.c
APP_OFILES = xmain.o
TEST_FILES = xmain0.c xmain1.c xmain2.c xmain3.c xmain4.c xmain5.c xmain6.c

IFLAGS = -g -I. -I/usr/lib/gcc/x86_64-linux-gnu/7/include
CFLAGS =   ${IFLAGS} -Wno-implicit
DEPFLAGS = ${IFLAGS}
CC     = gcc -m32
AS     = as -32

RCS     = Makefile ${HFILES} ${CFILES}

a.out: ${XTLIB} ${APP_OFILES} join.o
	${CC} ${CFLAGS} ${APP_OFILES} ${XTLIB} 

${XTLIB}: ${OFILES}
	ar cr ${XTLIB} ${OFILES}

ci:
	ci -u ${RCS}

clean:
	rm -f ${OFILES}	${APP_OFILES}

depend:
	makedepend ${DEPFLAGS} ${CFILES} ${SFILES}
# DO NOT DELETE THIS LINE - maketd DEPENDS ON IT

submit:
	turnin -c cis620s -p proj2 Makefile $(HFILES) $(CFILES) $(SFILES) $(TEST_FILES)