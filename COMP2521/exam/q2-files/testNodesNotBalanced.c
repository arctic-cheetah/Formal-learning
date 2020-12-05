/* testNodesNotBalanced.c 
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int nodesNotBalanced(BSTree t);

int main(int argc, char *argv[])
{
	char buffer[1024];

	char *line1 = fgets(buffer, sizeof(buffer), stdin);
	BSTree t = getBST(line1); 
	printf("\nDisplaying tree (sideways) \n"); 
	showBSTree(t);

	printf("\n -------  \n"); 	
	int ans = nodesNotBalanced(t);
	fprintf(stdout, "nodesNotBalanced(t) returns: %d \n", ans);
	printf(" -------  \n"); 	

	freeBSTree(t);

	return 0;
}

