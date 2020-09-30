				struct node *newDcurr = Dcurr;
					if (Dcurr == DifferenceList->head) {
						DifferenceList->head = Dcurr->next;
						free(newDcurr);
						Dprev = DifferenceList->head;
						Dcurr = Dprev;
					}
					else {
						Dprev->next = Dcurr->next;
						free(newDcurr);
						Dcurr = Dprev->next;
					}
