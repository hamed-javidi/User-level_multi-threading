/*Hamed Javidi, Azin Shamshirgaran
2738776, 2729460
Date of creation: 2/28/2020
Date of modification 3/29/2020
Date of modification 3/4/2020
Date of modification 3/5/2020
*/
#include <stdio.h>


int xidfoo, xidbar;
int x=0;
//Added:
const int Max=2000000;

int foo(int f)
{
   int i;
   for(i=0;i<20;i++){
      printf("This is foo %d, %d\n", f, x++);
	  //Added:
	  for(int z=0;z<Max;z++);
      //xthread_yield(xidbar);
   }
}

int bar(int p, int q)
{
   int j;
   for(j=0;j<20;j++){
      printf("This is bar %d, %d\n", p-q, x++);
	  //Added:
	  for(int z=0;z<Max;z++);
	  //Commented:
      //xthread_yield(xidfoo);
   }
}

xmain(int argc, char* argv[])
{
   xidfoo = xthread_create(foo, 1, 7);   
   xidbar = xthread_create(bar, 2, 32, 12);
   //Commented:
   //xthread_yield(xidfoo);
}


