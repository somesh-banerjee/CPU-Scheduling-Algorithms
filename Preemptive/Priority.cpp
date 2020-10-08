#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

struct process {
  int pid;
  int arrival_time;
  int burst_time;
  int priority;
  int start_time;
  int completion_time;
  int turnaround_time;
  int waiting_time;
  int response_time;
};
int main()
{
	cout<<"\t\t|| Priority Algorithm||\n";
	int i,j,n;
	float twt,ttat,trt;
	twt=ttat=trt=0;
  cout<<"Enter total processes: ";
  cin>>n;
	process *P = new process[n];
  int *burst_remaining = new int[n];
  int *is_completed = new int[n];
  memset(is_completed,0,sizeof(is_completed));
	cout<<"Enter AT-BT-Priority of Proccesses in order:\n";
	for(i=0;i<n;i++){
		cin>>P[i].arrival_time>>P[i].burst_time>>P[i].priority;
		P[i].pid=i+1;
		burst_remaining[i]=P[i].burst_time;
	}
	int current_time,completed;
	current_time=completed=0;
	while(completed != n) {
    int idx = -1;
    int mx = -1;
    for(int i = 0; i < n; i++) {
      if(P[i].arrival_time <= current_time && is_completed[i] == 0) {
        if(P[i].priority > mx) {
          mx = P[i].priority;
          idx = i;
        }
        else if(P[i].priority == mx) {
          if(P[i].arrival_time < P[idx].arrival_time) {
            mx = P[i].priority;
            idx = i;
          }
        }
      }
    }
    if(idx != -1) {
      if(burst_remaining[idx] == P[idx].burst_time) {
        P[idx].start_time = current_time;
      }
      burst_remaining[idx] -= 1;
      current_time++;
      if(burst_remaining[idx] == 0) {
        P[idx].completion_time = current_time;
        P[idx].turnaround_time = P[idx].completion_time - P[idx].arrival_time;
        P[idx].waiting_time = P[idx].turnaround_time - P[idx].burst_time;
        P[idx].response_time = P[idx].start_time - P[idx].arrival_time;
        ttat += P[idx].turnaround_time;
        twt += P[idx].waiting_time;
        trt += P[idx].response_time;
        is_completed[idx] = 1;
        completed++;
      }
    }
    else {
  		current_time++;
    }
  }
	cout<<"Process\tAT\tBT\tCT\tTAT\tWT\tRT\n";
	for(i=0;i<n;i++){
		cout<<i+1<<"\t"<<P[i].arrival_time<<"\t"<<P[i].burst_time<<"\t"<<P[i].completion_time<<"\t"<<P[i].turnaround_time<<"\t"<<P[i].waiting_time<<"\t"<<P[i].response_time<<endl;
	}
	cout<<"\nAverage waiting Time: "<<twt/n<<endl;
	cout<<"Average Turn Around Time: "<<ttat/n<<endl;
	cout<<"Average Response Time: "<<trt/n<<endl;
	return 0;
}
