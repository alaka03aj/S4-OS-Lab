#include <stdio.h>
#include <string.h>

struct Process {
    char name[20];
    int arrivalTime, turnaroundTime, burstTime, waitingTime, status, completionTime, priority;
} processes[20], temp;

struct GanttEntry {
    char name[20];
    int startTime, endTime;
} ganttChart[20];

void main() {
    int numProcesses, i, j, remainingProcesses, minIndex, processFound, ganttIndex, isIdle;
    float totalWaitingTime = 0.0, totalTurnaroundTime = 0.0;

    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &numProcesses);

    // Input process details
    for (i = 0; i < numProcesses; i++) {
        printf("\nENTER DETAILS OF PROCESS %d\n", i + 1);
        printf("PROCESS NAME: ");
        scanf(" %s", processes[i].name);
        printf("ARRIVAL TIME: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("BURST TIME: ");
        scanf("%d", &processes[i].burstTime);
        printf("PRIORITY: ");
        scanf("%d", &processes[i].priority);
        processes[i].status = 0;
    }

    // Initialize variables
    remainingProcesses = numProcesses;
    ganttIndex = 0;
    isIdle = 0;

    // Scheduling loop
    i=0;
    while (remainingProcesses > 0) {
        processFound = 0;
        // Find the process with the highest priority that is available for scheduling
        for (j = 0; j < numProcesses; j++) {
            if (i >= processes[j].arrivalTime && processes[j].status == 0) {
                if (processFound == 0) {
                    minIndex = j;
                    processFound = 1;
                } else if ((processes[minIndex].priority > processes[j].priority) ||
                           (processes[minIndex].priority == processes[j].priority && processes[minIndex].arrivalTime > processes[j].arrivalTime)) {
                    minIndex = j;
                }
            }
        }

        if (isIdle == 0 && processFound == 0) {
            strcpy(ganttChart[ganttIndex].name, "Idle");
            ganttChart[ganttIndex].startTime = i;
            i++;
            isIdle = 1;
        } else if (processFound == 1) {
            if (isIdle == 1) {
                ganttChart[ganttIndex].endTime = i;
                ganttIndex++;
                isIdle = 0;
            }
            strcpy(ganttChart[ganttIndex].name, processes[minIndex].name);
            processes[minIndex].status = 1;
            ganttChart[ganttIndex].startTime = i;
            ganttChart[ganttIndex].endTime = i + processes[minIndex].burstTime;
            i = ganttChart[ganttIndex].endTime;
            processes[minIndex].completionTime = ganttChart[ganttIndex].endTime;
            processes[minIndex].turnaroundTime = processes[minIndex].completionTime - processes[minIndex].arrivalTime;
            processes[minIndex].waitingTime = processes[minIndex].turnaroundTime - processes[minIndex].burstTime;
            ganttIndex++;
            remainingProcesses--;
        } else {
            i++;
        }
    }

    // Calculate total waiting and turnaround times
    for (i = 0; i < numProcesses; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    // Display process details
    printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
    for (i = 0; i < numProcesses; i++) {
        printf("%-15s\t%6d\t\t%6d\t\t%6d\n", processes[i].name, processes[i].completionTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    // Display Gantt chart
    printf("\nGANTT CHART\n");
    printf("-------------------------------------------------------------\n");
    printf("|");
    for (i = 0; i < ganttIndex; i++) {
        printf(" %-10s |", ganttChart[i].name);
    }
    printf("\n-------------------------------------------------------------\n");
    printf("0");
    for (i = 0; i < ganttIndex; i++) {
        printf("          %2d", ganttChart[i].endTime);
    }
    printf("\n-------------------------------------------------------------\n");

    // Display average waiting and turnaround times
    printf("\nAVERAGE WAITING TIME: %.2f", totalWaitingTime / numProcesses);
    printf("\nAVERAGE TURNAROUND TIME: %.2f\n", totalTurnaroundTime / numProcesses);
}
