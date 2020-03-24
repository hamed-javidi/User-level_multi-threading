/*Hamed Javidi, Azin Shamshirgaran
2738776, 2729460
Date of creation: 2/28/2020
Date of modification 3/29/2020
Date of modification 3/4/2020
Date of modification 3/5/2020
*/
#include <stdio.h>
#include <proc.h>

/*------------------------------------------------------------------------
 * userret  --  entered when a thread exits by return
 *------------------------------------------------------------------------
 */
void userret()
{
	//Added in order to handle other threads when the thread has not xthread_exit()
	while(!isEmpty(currxid)){			
		int jid;
		deq(currxid, &jid);		
		xtab[jid].xstate=XREADY;
	}
	if(xtab[currxid].xstate != XZOMBIE){
		xtab[currxid].xstate = XFREE;
		xtab[currxid].status = 0;
		xtab[currxid].jstatus = 0;
	}
	printf("XT: Old threads never die; they just fade away. (id:%d)\n",currxid);
    /* find the next runnable thread to trun */
   
   resched();
}

static int newxid()
{
    int i, xid;
    static int nextproc =0;
  
    for(i=0; i<NPROC; i++) { /* find a free process entry */
        xid = nextproc;
        if((++nextproc) >= NPROC)
             nextproc = 0;
        if(xtab[xid].xstate == XFREE)
             return(xid);
    }
    printf("Error: run out of process table ! \n"); 
    exit(1);
}

/*------------------------------------------------------------------------
 *  xthread_create  -  create a process to start running a procedure
 *------------------------------------------------------------------------
 */
int xthread_create(int *procaddr,int nargs, int args)
{
    WORD *saddr;              /* stack address */
    WORD *ap;  
    struct xentry *xptr;
    int xid;

    xid = newxid();	
    xptr = &xtab[xid];
    xptr->xstate = XREADY;
	
	    saddr = (WORD *) xptr->xbase;

    ap = (&args) + nargs;
    for(; nargs > 0; nargs--)
        *(--saddr) = *(--ap); /* copy args onto new process' stack */
    *(--saddr)  = (int)userret;   /* sooner or later you will be there */     
    *(--saddr)  = (int)procaddr;
    --saddr;           /* for frame ebp; it's not important !? */
    saddr -= 2;        /* 2 words for si and di */
    xptr->xregs[SP] = (int) saddr ;

    return(xid);
}
