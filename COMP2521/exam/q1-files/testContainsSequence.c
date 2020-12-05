// 
// testContainsSequence.c   ... 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

int containsSequence (List seq1, List seq2);


int main(int argc, char *argv[])
{
	char buffer[1024] ;


	char *line1=fgets(buffer, sizeof(buffer), stdin);
	List list1 = getList(line1);
	fprintf(stdout, "list1: ");
	showList(stdout, list1);

	char *line2=fgets(buffer, sizeof(buffer), stdin);
	List list2 = getList(line2);
	fprintf(stdout, "list2: ");
	showList(stdout, list2);

	int ans = containsSequence(list1, list2);

	fprintf(stdout, "answer: %d\n", ans);


	dropList(list1);
	dropList(list2);


	return 0;

}
