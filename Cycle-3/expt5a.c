//C Program to Simulate Priority Scheduling CPU scheduling Algorithm

#include <stdio.h>
#include <stdlib.h>

struct process{
	int burstTime, waitTime, priority, no;
}p[20],temp;

int main(){
	int n, totalWait = 0, totalTurn = 0;
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
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
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
