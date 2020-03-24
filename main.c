/*Hamed Javidi, Azin Shamshirgaran
2738776, 2729460
Date of creation: 2/28/2020
Date of modification 3/4/2020
*/
#include <stdio.h>
#include <proc.h>
#include <signal.h>

extern void xmain();

struct xentry xtab[10]; 
int currxid = 0;
int debug=0; 
void handler(){
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGALRM);
	sigprocmask(SIG_UNBLOCK, &set,NULL);
	xtab[currxid].xstate=XREADY;
	resched();
}


void main(int argc, char *argv[])
{
   register struct xentry *xptr;
   struct xentry m;
   int i;
   int xidxmain;
   
   if(argc>1)
	   debug=atoi(argv[1]);
	
   for(i=0 ; i < NPROC; i++){
      xptr = &xtab[i];
      xptr->xid = i;
      xptr->xlimit =  (WORD) malloc(STKSIZE);
      xptr->xbase = xptr->xlimit + STKSIZE - sizeof(WORD);
      xptr->xstate = XFREE;
	  xptr->jstatus=0;
	  //Added: initializing queue
	  xptr->head=0;
	  xptr->tail=0;
   }
	//Adding SIGALARM
	signal(SIGALRM,handler);
    /* the first thread runs user's xmain with id 0*/
    xidxmain = xthread_create(xmain, 2, argc, argv);
   
 
   
   //Added
   ualarm(20000);
   xtab[xidxmain].xstate = XRUN; 
   ctxsw(m.xregs, xtab[xidxmain].xregs);
   /* never be here */
}


