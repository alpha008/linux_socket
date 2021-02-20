#include <stdio.h>
#include "main.h"
#include "fun.h"
#include "fund.h"


int main()
{
	printf("hello world\n");
	mainfunc();
    stafunc();
    dyfunc();
#ifdef _MACRO
	printf("macro test\n");
#endif

#ifdef _ZJX
	printf("ZJX test\n");
#endif
	return 0;
}
