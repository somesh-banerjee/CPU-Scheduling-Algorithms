#include <iostream>
using namespace std;

int main()
{
	cout<<"\t\t||Shortest Job First Algorithm||\n";
	int i,j,n;
	float twt,ttat;
	twt=ttat=0;
  cout<<"Enter total processes: ";
  cin>>n;
	int *bt = new int[n];
	int *at = new int[n];
	int *wt = new int[n];
	int *tat = new int[n];
	int *prc = new int[n];
	int *ct = new int[n];
	cout<<"Enter AT BT of Proccesses in order:\n";
	for(i=0;i<n;i++){
		cin>>at[i]>>bt[i];
		prc[i]=i+1;
	}
	//Sorting based on AT and BT for SJF
	for(i=0;i<n;i++){
		for(j=i;j<n;j++){
			if(at[i]>at[j]){
				int tmp=at[i];
				at[i]=at[j];
				at[j]=tmp;
				tmp=bt[i];
				bt[i]=bt[j];
				bt[j]=tmp;
				tmp=prc[i];
				prc[i]=prc[j];
				prc[j]=tmp;
			}
			else if(at[i]==at[j] && bt[i]>bt[j]){
				int tmp=at[i];
				at[i]=at[j];
				at[j]=tmp;
				tmp=bt[i];
				bt[i]=bt[j];
				bt[j]=tmp;
				tmp=prc[i];
				prc[i]=prc[j];
				prc[j]=tmp;
			}
		}
	}
	ct[0]=at[0]+bt[0];
	tat[0]=ct[0]-at[0];
	wt[0]=tat[0]-bt[0];
	ttat+=tat[0];
	twt+=wt[0];
	for(i=1;i<n;i++){
		int low,ilow=i;
		low=bt[i];
		for(j=i;j<n;j++){
			if(bt[j]<low && at[j]<=ct[i-1]){
				low=bt[j];
				ilow=j;
			}
		}
		j=ilow;
		int tmp=at[i];
		at[i]=at[j];
		at[j]=tmp;
		tmp=bt[i];
		bt[i]=bt[j];
		bt[j]=tmp;
		tmp=prc[i];
		prc[i]=prc[j];
		prc[j]=tmp;
		ct[i]=ct[i-1]+bt[i];
		tat[i]=ct[i]-at[i];
		wt[i]=tat[i]-bt[i];
		ttat+=tat[i];
		twt+=wt[i];
	}
	cout<<"Process\tAT\tBT\tCT\tTAT\tWT\n";
	for(i=0;i<n;i++){
		cout<<prc[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<endl;
	}
	cout<<"\nAverage waiting Time: "<<twt/n<<endl;
	cout<<"Average TAT Time: "<<ttat/n<<endl;
	return 0;
}
