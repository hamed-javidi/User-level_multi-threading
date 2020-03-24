/*Hamed Javidi, Azin Shamshirgaran
2738776, 2729460
Date of creation: 2/28/2020
Date of modification 3/29/2020
Date of modification 3/4/2020
Date of modification 3/5/2020
*/
#include <proc.h>


char isEmpty(int tid){
	return xtab[tid].head == xtab[tid].tail?1:0;
}

char isFull(int tid){
	return (xtab[tid].tail - xtab[tid].head) >= (Qsize-1)?1:0;
}

char addq(int tid, int a){ 
	if(isFull(tid))
		return 0; //queue is full
	int *tail=&xtab[tid].tail;	
	xtab[tid].q[*tail]=a;
	*tail=(++(*tail))%Qsize;	
	return 1; // success
	
	
	
}
 char deq(int tid, int * a){
	if(isEmpty(tid))
		return 0; //queue is empty
	int *head=&xtab[tid].head;
	*a=xtab[tid].q[*head];
	*head=(++(*head))%Qsize;
	return 1;	
}
Xtab_show(int tid){
	printf("TID: %d",tid);
	for(int i=0; i<NPROC; i++){
		printf("xtab %d : head : %d tail : %d\n" , i , xtab[i].head, xtab[i].tail);
		int size=xtab[i].tail-xtab[i].head;
		for(int j=0; j<size; j++){
			printf("XTAB %d[%d]=%d\n",i,j,xtab[i].q[j]);
		}
	}
}

void xthread_exit(int status){
	
	while(!isEmpty(currxid)){			
		int jid;
		deq(currxid, &jid);		
		xtab[jid].jstatus=status;
		xtab[jid].xstate=XREADY;
	}
	xtab[currxid].status=status;
	xtab[currxid].xstate=XZOMBIE;
}


int xthread_join(int tid, int *tid_retval){
	int usec=ualarm(0,0);	
	if(debug)
		printf("In Join func, currxid: %d, tid: %d\n",tid, currxid);
	if(tid==currxid)
		return -1;
	if(xtab[tid].xstate==XFREE){
		return -2;
	}
	
	if(xtab[tid].xstate != XZOMBIE){
		xtab[currxid].xstate=XJOIN;
		addq(tid,currxid);			
		if(debug){
			printf("In Join function, queue of thread with xid %d,  just before calling resched()\n", currxid);	
			Xtab_show(currxid);
		}
		resched();
		if(debug){
			printf("In Join function, queue of thread with xid %d,  just After calling resched()", currxid);			
			Xtab_show(currxid);	
		}		
		*tid_retval=xtab[currxid].jstatus;		
		ualarm(usec,0);		
		return 0;
	}
	else{ //tid xstate is Zombie
		if(debug){
			printf("In Join function, queue of thread with xid %d,  just before calling resched()\n", currxid);	
			Xtab_show(currxid);
		}
		if(debug)
			printf("Zombie case: xtab[tid].status: %d\n",xtab[tid].status);
		*tid_retval=xtab[tid].status;
		xtab[tid].status=0;
		xtab[tid].xstate=XFREE;
		ualarm(usec,0);
		return 0;
	}
	
		
}