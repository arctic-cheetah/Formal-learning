treeLab : treeLab.o BSTree.o tree.o
	gcc -o treeLab treeLab.o BSTree.o 

treeLab.o : treeLab.c BSTree.h 
	gcc -Wall -Werror -c treeLab.c

BSTree.o : BSTree.c BSTree.h
	gcc -Wall -Werror -c BSTree.c
	
tree.o : tree.c tree.h
	gcc -Wall -Werror -c tree.c

