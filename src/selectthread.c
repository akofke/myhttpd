//Code for the thread that selects a handler thread to do a job after a job was received from the listener thread

#include <myhttpd.h>
#include <queue>

int selector_thread(int numthread, bool sorttype){ // sorttype: true for FCFS, false for SJF
	int curthreads = 0;
	if (sorttype){ //First Come First Serve implementation
		
	}
	else { //Shortest Job First implementation
		
	}
	return 0;
}
