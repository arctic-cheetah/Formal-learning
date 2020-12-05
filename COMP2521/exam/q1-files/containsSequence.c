// containsSequence.c ... implementation of containsSequence function

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

/* 
You will submit only this one file.

Implement the function "containsSequence" below. Read the exam paper for 
detailed specification and description of your task.  

- DO NOT modify code in the file List.h . 
- If you wish, you can add helper static functions/variable in this file.  
- DO NOT add "main" function in this file. 

*/

/* 
We say seq1 contains seq2 if all numbers in seq2 also appear in
seq1, in the same order as they appear in seq2. 

For example: 

seq1: 10, 5, 23, 56, 8, 92, 5, 7
seq2: 5, 8, 92
containsSequence(seq1, seq2) should return 1.

seq1: 10, 5, 23, 56, 8, 92, 5, 7
seq2: 8, 5, 92
containsSequence(seq1, seq2) should return 0.

seq1: 10, 5, 23, 56, 8, 92, 5, 7
seq2: 25, 23, 56, 8
containsSequence(seq1, seq2) should return 0.

seq1: 10, 5, 23, 56, 8, 92, 5, 7
seq2: 10, 7
containsSequence(seq1, seq2) should return 1.	

seq1: 10, 5, 23, 56, 8, 92, 5, 7
seq2: 8, 92, 7
containsSequence(seq1, seq2) should return 1.	

seq1: 10, 5, 23, 56, 8, 92, 5, 7
seq2: 56
containsSequence(seq1, seq2) should return 1.	

seq1: 10, 5, 23, 56, 8, 92, 5, 7
seq2: 5, 5, 7
containsSequence(seq1, seq2) should return 1.	

*/


int containsSequence (List seq1, List seq2) {

	//Cases:

	//seq1 < seq2 --- 0
	//seq1 is out of order from seq2 -- 0
	//seq1 is ordered with seq2 -- 1
	//seq1 is missing numbers from seq2 (include duplicates) -- 0

	Node *curr1 = seq1->first;
	Node *curr2 = seq2->first;

	//Only traverse through the seq2 and seq1 once.

	while (curr2 != NULL && curr1 != NULL) {
		
		if (curr2->value == curr1->value) {
			curr2 = curr2->next;
			curr1 = curr1->next;
		}
		//Numbers are different
		//and continue checking 
		else {
			curr1 = curr1->next;
		}
	}
	int isContained = 0;
	
	//seq1 ended first, followed by seq2
	//seq1 does not contain seq2
	if (curr2 != NULL && curr1 == NULL) {
		isContained = 0;
	}
	//seq2 ended first followed by seq1
	//seq1 contains seq2
	else if (curr2 == NULL && curr1 != NULL) {
		isContained = 1;
	}
	//seq1 and seq2 ended simultaneously
	//Check if the last values are the same
	else if (curr2 == NULL && curr2 == NULL) {
		if (seq1->last->value == seq2->last->value) {
			isContained = 1;
		}
	}
	return isContained; 

}



