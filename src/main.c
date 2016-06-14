//Code for starting the applications, launches the server thread and the thread selector thread
#include <stdio.h>
#include <myhttpd.h>

using namespace std;

int main(int argc, char* argv[]){
	int result;
	int numthread = 1;
	bool sorttype = true;
	if (fork()==0){
		cout<<"Starting server thread"<<endl;
		result = server();//add arguments as needed to be passed to the server.
		cout<<"Error code "<<result<<" in server thread"<<endl;
	}
	else if (fork()==0){
				cout<<"Starting selector thread"<<endl;
				result = thread_selector(numthread, sorttype); // sorttype: true for FCFS, false for SJF
				cout<<"Error code "<<result<<" in selector thread"<<endl;
	}
	return 0;
}
