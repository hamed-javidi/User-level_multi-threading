/*    proc.h    */
#include <stdio.h>
#include <stdlib.h>

typedef int WORD;

#define PNREGS 5

#define NPROC 10

#define SP     0

/* state */
#define XFREE    0
#define XREADY   1
#define XRUN     2
//Added:
#define XZOMBIE  3
#define XJOIN	 4
//Added struct queue:
#define Qsize 10

struct xentry  {
       int  xid;
       WORD xregs[PNREGS];    /* save SP */
       WORD xbase;
       WORD xlimit;
       int  xstate;
	   int status;
	   //Added: declaring queue
	   int head;
	   int tail;
	   int q[Qsize]; //max lentgh of queue=10
	   int jstatus;
};

#define STKSIZE 8192 

extern struct xentry xtab[];

extern int currxid;
extern int debug;


	