#include <iostream>
using namespace std;

int main()
{
	cout<<"\t\t||First Come First Serve Algorithm||\n";
	int i,j,n;
	float twt,ttat;
	twt=ttat=0;
  cout<<"Enter total processes: ";
  cin>>n;
	int *bt = new int[n];
	int *at = new int[n];
	int *wt = new int[n];
	int *tat = new int[n];
	cout<<"Enter AT BT of Proccesses in order:\n";
	for(i=0;i<n;i++){
		cin>>at[i]>>bt[i];
		long s=0;
		for(j=0;j<i;j++){
			s+=bt[j];
		}
		wt[i]=s-at[i];
		twt+=wt[i];
		if(wt[i]<0)	wt[i]=0;
		tat[i]=wt[i]+bt[i];
		ttat+=tat[i];
	}
	cout<<"Process\tAT\tBT\tTAT\tWT\n";
	for(i=0;i<n;i++){
		cout<<i+1<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<endl;
	}
	cout<<"\nAverage waiting Time: "<<twt/n<<endl;
	cout<<"Average TAT Time: "<<ttat/n<<endl;
	return 0;
}
