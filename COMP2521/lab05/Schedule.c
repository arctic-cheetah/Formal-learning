// Schedule ADT implementation

#include <stdio.h>
#include <stdlib.h>

#include "Schedule.h"
#include "Time.h"
#include "Tree.h"

struct schedule {
    Tree times;
    int  count;
};

// Creates a new schedule
Schedule ScheduleNew(void) {
    Schedule s = malloc(sizeof(*s));
    if (s == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    s->times = TreeNew();
    s->count = 0;
    return s;
}

// Frees all memory associated with a given schedule
void ScheduleFree(Schedule s) {
    TreeFree(s->times);
    free(s);
}

// Gets the number of times added to the schedule
int  ScheduleCount(Schedule s) {
    return s->count;
}

// Attempts to schedule a new landing time. Returns true if the time was
// successfully added, and false otherwise.
bool ScheduleAdd(Schedule s, Time t) {
	//GLB(Greatest lower bound) --> latest time that is earlier or equal to
    //LUB(Least upper bound) --> earliest time that is later or equal to
    
    //Get times
    Time GLB = TreeFloor(s->times, t);
    Time LUB = TreeCeiling(s->times, t);
    
    //Use TimeCmp to find the difference in time.
    //Warning! Need to find difference in minutes,
    //Must account if TimeCmp returns difference in hours, days, etc
   
    
    //Consider all cases where we can add a landing time:
    //Otherwise false
    
    //If there are no landing times
    if (GLB == NULL && LUB == NULL ) {
    	TreeInsert(s->times, t);
    	s->count++;
    	return true;
    }
    //There exists landing time/s later than t
    //yet there are no earlier times
    //This means t is the earliest time!
    //Yet we need to check if it is greater than 10 minutes away
    //From the latest time
    if (GLB == NULL && LUB != NULL) {
    	int i = 0;
    	while (i <= 59) {
    		if ( TimeCmp(LUB, TimeAddMinutes(t, i)) == 0 && i <= 10) {
    			return false;
    		}
    		i +=1;
    	}
		
    	TreeInsert(s->times, t);
    	s->count++;
    	return true;
    }
    //There exists landing time/s earlier than t
    //yet there are no later times
    //t is the latest time!
    //Yet we need to check if it is greater than 10 minutes away
    if (GLB != NULL && LUB == NULL) {
    	int i = 0;
    	while (i <= 59) {
    		if ( TimeCmp(GLB, TimeSubtractMinutes(t, i)) == 0 && i <= 10) {
    			return false;
    		}
    		i +=1;
    	}
    	TreeInsert(s->times, t);
    	s->count++;
    	return true;
    }
    
    
    //Obtain time difference between GLB and LUB
    int i = 0;
    int TimeDiff = 0;
    while (i <= 59 && TimeCmp(TimeAddMinutes(GLB, i), LUB) != 0) {
    	TimeDiff +=1;
    	i+=1;
    }
    // Outside 10 minutes of the two latest and earliest landings
    if ( TimeDiff > 20) {
    	TreeInsert(s->times, t);
    	s->count++;
    	return true;
    }
    
    //Otherwise we have a landing time that is within 10 minutes
    //of another time
    return false;
}

// Shows  all  the landing times in the schedule. If mode is 1, only the
// times are shown. If mode is 2, the underlying data structure is shown
// as well.
void ScheduleShow(Schedule s, int mode) {
    if (mode == 1) {
        TreeList(s->times);
    } else if (mode == 2) {
        TreeShow(s->times);
    }
}
