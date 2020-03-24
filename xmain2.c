/*Hamed Javidi, Azin Shamshirgaran
2738776, 2729460
Date of creation: 2/28/2020
Date of modification 3/29/2020
Date of modification 3/4/2020
Date of modification 3/5/2020
*/
#include <stdio.h>

int xthread_join(int tid, int *tid_retval);
void xthread_exit(int status);

int xidfoo, xidoof;
int x=0;
//Added:
const int Max=2000000;

int foo(int f)
{
   int status;
   int ret;  
	printf("***Enter foo  .... \n");
	ret=xthread_join(xidoof, &status);
   printf("***foo:join oof : %d , ret: %d\n",status, ret);
}

int oof(int j)
{
   printf("***oof: exit with %d\n ", j);
   xthread_exit(j);
   
}

xmain(int argc, char* argv[])
{
   xidfoo = xthread_create(foo, 1, 7);
   xidoof = xthread_create(oof, 1, 12345);
   //Commented:
   //xthread_yield(xidfoo);
}


