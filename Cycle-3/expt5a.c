//C Program to Simulate Priority Scheduling CPU scheduling Algorithm

#include <stdio.h>
#include <stdlib.h>

struct process{
	int burstTime, waitTime, priority, no;
}p[20];

int main(){
	int n, totalWait = 0, totalTurn = 0;
	int temp;
	printf("Enter number of process: ");
	scanf("%d",&n);
	//reading process related data
	for (int i=0; i<n; i++){
		p[i].no = i;
		printf("Enter burst time of #%d: ",p[i].no+1);
		scanf("%d",&p[i].burstTime);
		printf("Ente priority of #%d: ", p[i].no+1);
		scanf("%d",&p[i].priority);
	}
	//bubble sort
	for (int i=0; i<n; i++){
		for (int j=0; j<n-i-1; j++){
			if (p[j].priority > p[j+1].priority){
				//exchanging burst time
				temp = p[j].burstTime;
				p[j].burstTime = p[j+1].burstTime;
				p[j+1].burstTime = temp;
				//exchanging pno
				temp = p[j].no;
				p[j].no = p[j+1].no;
				p[j+1].no = temp;
				//exchanging priority
				temp = p[j].priority;
				p[j].priority = p[j+1].priority;
				p[j+1].priority = temp;
			}
		}
	}
	
	printf("\nProcess\t\tStartTime\tEndingTime\tWaitingTime\tPriority\tTurn Around Time");
	for (int i=0; i<n; i++){
		printf("\nProcess #%d%10d%16d%16d%16d%16d",p[i].no+1,p[i].waitTime,p[i].waitTime+p[i].burstTime,p[i].waitTime,p[i].priority,p[i].waitTime+p[i].burstTime);
		p[i+1].waitTime = p[i].waitTime+p[i].burstTime;
		totalWait = totalWait+p[i].waitTime;
		totalTurn = totalTurn + p[i].waitTime + p[i].burstTime;
	}
	printf("\nAverage waiting time: %.2f",totalWait/(float)n);
	printf("\nAverage turnaround time: %.2f\n",totalTurn/(float)n);
	
	return 0;
}
