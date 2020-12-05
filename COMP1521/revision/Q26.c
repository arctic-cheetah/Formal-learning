#include <stdio.h>


int main () {

	int x = 0;
	int *p;
	
	p = &x;
	
	printf("%p\n", p);
	printf("%d\n", *p);
	printf("%p\n", &x);
	printf("%d\n\n", x);
	
	x = 14;
	printf("%p\n", p);
	printf("%d\n", *p);
	printf("%p\n", &x);
	printf("%d\n\n", x);
	
	*p = 3;
	printf("%p\n", p);
	printf("%d\n", *p);
	printf("%p\n", &x);
	printf("%d\n\n", x);
	
	x = (int)p;
	printf("%p\n", p);
	printf("%d\n", *p);
	printf("%p\n", &x);
	printf("%d\n\n", x);
	
	x = (int)&p;
	printf("%p\n", p);
	printf("%d\n", *p);
	printf("%p\n", &x);
	printf("%d\n\n", x);
	
	p = NULL;
	printf("%p\n", p);
	printf("%d\n", *p);
	printf("%p\n", &x);
	printf("%d\n\n", x);
	
	*p = 1;
	printf("%p\n", p);
	printf("%d\n", *p);
	printf("%p\n", &x);
	printf("%d\n\n", x);
	
	
}


























