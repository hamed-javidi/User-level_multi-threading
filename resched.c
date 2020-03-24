/*Hamed Javidi, Azin Shamshirgaran
2738776, 2729460
Date of creation: 2/28/2020
Date of modification 3/29/2020
Date of modification 3/4/2020
Date of modification 3/5/2020
*/
/* resched.c  -  resched */
#include <stdio.h>
#include <proc.h>
#include <signal.h>

/*------------------------------------------------------------------------
 * resched  --  find a live thread to run
 *
 *------------------------------------------------------------------------
 */
void resched()
{
    register struct  xentry  *cptr;  /* pointer to old thread entry */
    register struct  xentry  *xptr;  /* pointer to new thread entry */
    int i,next;

    cptr = &xtab[currxid];	
    next = currxid ;
    for(i=0; i<NPROC; i++) { 
        if( (++next) >= NPROC){			
             next = 0;
		}
        if(xtab[next].xstate == XREADY) {			
            xtab[next].xstate = XRUN;
            xptr = &xtab[next];
            currxid = next;
			//Added
			ualarm(20000);			
            ctxsw(cptr->xregs,xptr->xregs);			
            return;
        }
    }
	printf("XT: no threads to run!\n");
    exit(0);
}


