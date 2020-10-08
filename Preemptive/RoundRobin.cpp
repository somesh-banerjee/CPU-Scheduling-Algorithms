#include <iostream>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool compare_arrival(process p1, process p2)
{
    return p1.arrival_time < p2.arrival_time;
}

bool compare_pid(process p1, process p2)
{
    return p1.pid < p2.pid;
}

int main() {
  cout<<"\t\t|| Round Robin Algorithm ||\n";
    int i,n,tq;
    float twt,ttat,trt;
  	twt=ttat=trt=0;
    int idx;
    cout<<"Enter total processes and time quantum: \n";
    cin>>n>>tq;
  	process *p = new process[n];
    int *burst_remaining = new int[n];
  	cout<<"Enter AT-BT of Proccesses in order:\n";
  	for(i=0;i<n;i++){
  		cin>>p[i].arrival_time>>p[i].burst_time;
  		p[i].pid=i+1;
  		burst_remaining[i]=p[i].burst_time;
  	}
    sort(p,p+n,compare_arrival);
    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    int mark[100];
    memset(mark,0,sizeof(mark));
    mark[0] = 1;
    while(completed != n) {
        idx = q.front();
        q.pop();
        if(burst_remaining[idx] == p[idx].burst_time) {
            p[idx].start_time = max(current_time,p[idx].arrival_time);
            current_time = p[idx].start_time;
        }
        if(burst_remaining[idx]-tq > 0) {
            burst_remaining[idx] -= tq;
            current_time += tq;
        }
        else {
            current_time += burst_remaining[idx];
            burst_remaining[idx] = 0;
            completed++;
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
            ttat += p[idx].turnaround_time;
            twt += p[idx].waiting_time;
            trt += p[idx].response_time;
        }
        for(int i = 1; i < n; i++) {
            if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
        }
        if(burst_remaining[idx] > 0) {
            q.push(idx);
        }
        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(burst_remaining[i] > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }
    sort(p,p+n,compare_pid);
    cout<<"Process\t"<<"AT\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<endl;
    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<p[i].response_time<<"\t"<<endl;
    }
    cout<<"Average Turnaround Time = "<<ttat/n<<endl;
    cout<<"Average Waiting Time = "<<twt/n<<endl;
    cout<<"Average Response Time = "<<trt/n<<endl;
}
